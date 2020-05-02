
boolean isLoggingEnabled = false;

void initLogger() {
  isLoggingEnabled = doesFileExist(*confFileLogger);
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
