
const char *logFileGeneric = "SENSORS.LOG";

const char *logFileHeader = "Time,Hum,Tmp,CO,NO2";
const char *logFileSeparator = "#,#,#,#,#";

boolean isLoggingEnabled = false;
boolean isLogFileReady = false;
File logFile;

void initLogger() {
  isLoggingEnabled = doesFileExist(*confFileLogger);

  if(isLoggingEnabled) {
    return openLoggerFile();
  }

  return true;
}

boolean enableLogger() {
  if(createBlankFile(*confFileLogger)) {
    isLoggingEnabled = true;
    return true;
  } else {
    return false;
  }
}

boolean disableLogger() {
  if(deleteFile(*confFileLogger)) {
    isLoggingEnabled = false;
    return true;
  } else {
    return false;
  }
}

boolean openLoggerFile() {
  if(isSDCardReady && !isLogFileReady) {
    logFile = SD.open(logFileGeneric, FILE_WRITE);
    
    if(logFile) {
      // Move to the end of the file...
      logFile.seek(logFile.size());
      logFile.write(logFileSeparator);
      logFile.write("\n");
      logFile.write(logFileHeader);
      logFile.write("\n");
      logFile.flush();
      isLogFileReady = true;
      return true;
    }
  }

  return false;
}

boolean closeLoggerFile() {
  if(isSDCardReady && isLogFileReady) {
    logFile.flush();
    logFile.close();
    isLogFileReady = false;
  }
  
  return false;
}

// Returns true if the values were able to be logged and were ultimately logged.
boolean logSensorValues() {
  if(isLoggingEnabled && isSDCardReady && logFile && isLogFileReady) {
    // Logging stuff...
    
    // time
    logFile.write(millis());
    logFile.write(",");

    // hum
    logFile.write(getHumidity());
    logFile.write(",");
    
    // tmp
    logFile.write(getTemperature());
    logFile.write(",");
    
    // CO
    logFile.write(getCarbonMonoxyde());
    logFile.write(",");
    
    // NO2
    logFile.write(getNO2());
    logFile.write("\n");
    
    logFile.flush();
    
    return true;
  }

  return false;
}
