# -----------------------------
# Install packages
# -----------------------------
install.packages(c("tidyverse", "tidymodels", "skimr", "GGally", "corrplot", "kknn"))

# -----------------------------
# Load libraries
# -----------------------------
library(tidyverse)
library(tidymodels)
library(GGally)
library(corrplot)
library(yardstick)
library(kknn)

# -----------------------------
# Load and inspect data set
# -----------------------------
data <- read.csv("levels_abt_s4.csv")

View(data) # Opens the data set
str(data) # Shows the type and structure of the data
dim(data) # 5000 rows and 37 features
summary(data) # Stats of the data set

# -----------------------------
# EDA
# -----------------------------

# Target variable distribution
ggplot(data, aes(x = completed)) +
  geom_bar()

# Distribution of all features in the data set if numeric
data %>%
  select(where(is.numeric)) %>%
  pivot_longer(cols = everything()) %>%
  ggplot(aes(x = value)) +
  geom_histogram(bins = 30) +
  facet_wrap(~name, scales = "free")

# Correlation analysis between the features if numeric
GGally::ggcorr(data %>% select(where(is.numeric)))

# Check for missing data
colSums(is.na(data))

# Check for outliers
data %>%
  select(where(is.numeric)) %>%
  pivot_longer(cols = everything()) %>%
  ggplot(aes(y = value)) +
  geom_boxplot() +
  facet_wrap(~name, scales = "free")

# -----------------------------
# MACHINE LEARNING MODELS
# Logistic Regression and K-NN
# -----------------------------

# Target variable, format for classification
data$completed <- factor(data$completed, levels = c("0", "1"))

# -----------------------------
# Temporal Proxy Split training and testiing 80/20
# -----------------------------

# Sorted by seed
data <- data %>% arrange(seed)

# 80% cutoff for training data
split_point <- floor(0.8 * nrow(data))

# Split for training and test sets
train <- data[1:split_point,]
test  <- data[(split_point + 1):nrow(data),]

# -----------------------------
# Validation split
# -----------------------------

# Split again for validation set
set.seed(123)

val_split <- initial_split(train, prop = 0.8)

train_data <- training(val_split)
val_data   <- testing(val_split)

# -----------------------------
# Pre-processing, applied to both models
# -----------------------------

recipe_obj <- recipe(completed ~ ., data = train_data) %>%
  update_role(level_id, new_role = "ID") %>%
  update_role(seed, new_role = "ID") %>% # Remove seed and level_id as not used as predictors
  step_impute_median(all_numeric_predictors()) %>% # Handle the missing values
  step_normalize(all_numeric_predictors()) # Standardize num values, Standard Deviation = 1, Mean = 0

# -----------------------------
# MODEL 1: Logistic Regression
# -----------------------------
model1 <- logistic_reg() %>%
  set_engine("glm") %>% # Engine used glm
  set_mode("classification")

# Combining model and pre-processing into workflow
wf1 <- workflow() %>%
  add_recipe(recipe_obj) %>%
  add_model(model1)

# Train the model
fit1 <- fit(wf1, train_data)

# -----------------------------
# MODEL 2: K-NN
# -----------------------------

# Range for K values
knn_grid <- seq(3, 25, 2)

# Create results table
KNN_results <- tibble(
  k = knn_grid,
  accuracy = NA_real_
)

# Loop through each K value
for (i in seq_along(knn_grid)) {
  k_val <- knn_grid[i] # get current K
  
  # Define model with current K
  model <- nearest_neighbor(neighbors = k_val) %>%
    set_engine("kknn") %>% # Engine used kknn
    set_mode("classification")
  
  # Create workflow
  wf2 <- workflow() %>%
    add_recipe(recipe_obj) %>%
    add_model(model)
  
  # Train model
  fit <- fit(wf2, train_data)
  
  # Predict on validation set
  preds <- predict(fit, val_data, type = "class") %>%
    bind_cols(val_data)
  
  # Store the accuracy
  KNN_results$accuracy[i] <- accuracy(
    preds,
    truth = completed,
    estimate = .pred_class
  )$.estimate
}

# Select best K value
best_k <- KNN_results %>%
  arrange(desc(accuracy)) %>%
  slice(1)

best_k

# Train final model using best K value
final_model <- nearest_neighbor(neighbors = best_k$k) %>%
  set_engine("kknn") %>%
  set_mode("classification")

final_wf2 <- workflow() %>%
  add_recipe(recipe_obj) %>%
  add_model(final_model)

fit2 <- fit(final_wf2, train_data)

# -----------------------------
# MODEL 1 - Validation
# -----------------------------
pred_class1 <- predict(fit1, val_data, type = "class")
pred_prob1  <- predict(fit1, val_data, type = "prob")

pred1 <- bind_cols(val_data, pred_class1, pred_prob1)

# -----------------------------
# MODEL 1 - Test
# -----------------------------
test_class1 <- predict(fit1, test, type = "class")
test_prob1  <- predict(fit1, test, type = "prob")

test1 <- bind_cols(test, test_class1, test_prob1)

# -----------------------------
# MODEL 2 - Validation
# -----------------------------
pred_class2 <- predict(fit2, val_data, type = "class")
pred_prob2  <- predict(fit2, val_data, type = "prob")

pred2 <- bind_cols(val_data, pred_class2, pred_prob2)

# -----------------------------
# MODEL 2 - Test
# -----------------------------
test_class2 <- predict(fit2, test, type = "class")
test_prob2  <- predict(fit2, test, type = "prob")

test2 <- bind_cols(test, test_class2, test_prob2)

# -----------------------------
# RESULTS
# -----------------------------

# Confusion matrices to show errors of classification
conf_mat(pred1, truth = completed, estimate = .pred_class)
conf_mat(pred2, truth = completed, estimate = .pred_class)
conf_mat(test1, truth = completed, estimate = .pred_class)
conf_mat(test2, truth = completed, estimate = .pred_class)

acc_m1_val  <- accuracy(pred1, truth = completed, estimate = .pred_class)
acc_m1_test <- accuracy(test1, truth = completed, estimate = .pred_class)

acc_m2_val  <- accuracy(pred2, truth = completed, estimate = .pred_class)
acc_m2_test <- accuracy(test2, truth = completed, estimate = .pred_class)

results <- tibble(
  Model = c("Logistic Regression", "Logistic Regression",
            "K-NN", "K-NN"),
  Dataset = c("Validation", "Test",
              "Validation", "Test"),
  Accuracy = c(
    acc_m1_val$.estimate,
    acc_m1_test$.estimate,
    acc_m2_val$.estimate,
    acc_m2_test$.estimate
  )
)

results