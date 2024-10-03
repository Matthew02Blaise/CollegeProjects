#Matthew O'Rourke Bourke, K00287407

install.packages("xlsx")

library ("xlsx")

data <- read.xlsx("C:\\Users\\matto\\Desktop\\project\\Weather Data for Assessment.xlsx",sheetIndex=1)

print(data)

#1
x = (data$humidity)
y = (data$air.pressure)

plot (x,y)

#2
x2 = (data$windspeed)
y2 = (data$gust.speed)

plot (x2,y2)

#3
reg = lm(y2 ~ x2)

plot(x2,y2)
abline(reg, col="red")

