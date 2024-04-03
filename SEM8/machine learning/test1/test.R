library(readr)
data <- read_csv("C:/Programming/KPI_Labs/SEM8/machine learning/test1/Q1_getdata_data_ss06hid.csv")

agricultureLogical <- with(data, ACR == 3 & AGS == 6)
vec <- which(agricultureLogical)
print(vec)

names <- colnames(data)
split <- strsplit(names, "wgtp")
split[123]

acs <- read_csv("C:/Programming/KPI_Labs/SEM8/machine learning/test1/Q5_getdata_data_ss06pid.csv")
sqldf("select pwgtp1 from acs where AGEP < 50")
sqldf("select distinct AGEP from acs")

library(jpeg)
picture <- readJPEG("C:/Programming/KPI_Labs/SEM8/machine learning/test1/Q7_getdata_jeff.jpeg", native=TRUE)
flat_img <- as.vector(picture)
quantiles <- quantile(flat_img, probs = c(0.3, 0.8))
print(quantiles)

library(XML)
library(methods)
file_xml <- xmlParse(file = "C:/Programming/KPI_Labs/SEM8/machine learning/test1/Q8_data.xml")
print(file_xml)

restaurants <- read_csv("C:/Programming/KPI_Labs/SEM8/machine learning/test1/Q9_getdata_data_GDP.csv")
mean(restaurants$GDP)

library(quantmod)
amzn <- getSymbols("AMZN", auto.assign=FALSE)
sampleTimes <- index(amzn)
# load dates
sampleDates <- as.Date(sampleTimes)
# extract weekdays and years
years <- format(sampleDates, "%Y")
weekdays <- weekdays(sampleDates)
# count
count_Mondays <- sum(years == "2012" & weekdays == "Monday")
count_2012 <- sum(years == "2012")
print(count_2012)
print(count_Mondays)

library(nlme)
library(lattice)
xyplot(weight ~ Time | Diet, BodyWeight)

library(lattice)
library(datasets)
data(airquality)
p <- xyplot(Ozone ~ Wind | factor (Month), data = airquality)
print(p)
