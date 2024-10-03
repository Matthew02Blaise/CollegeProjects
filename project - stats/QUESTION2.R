#Matthew O'Rourke Bourke K00287407

install.packages("xlsx")

library ("xlsx")

data <- read.xlsx("C:\\Users\\matto\\Desktop\\project\\Weather Data for Assessment.xlsx",sheetIndex=1)

print(data)

#Humidity
#1
min = min(data$humidity)

print (min)

#2
max = max(data$humidity)

print (max)

#3
range = max - min

print(range)

#4
mean = mean(data$humidity)

print (mean)

#5
median = median(data$humidity)

print (median)

#6
stdDev = sd(data$humidity)

print (stdDev)

#7
length = length(data$humidity)

print (length)

#8
variance = var(data$humidity)

print (variance)

#9
popSD = sqrt(variance*(length-1)/length)

print (popSD)

#10
percentile35 = quantile(data$humidity,0.35,type=6)

print (percentile35)