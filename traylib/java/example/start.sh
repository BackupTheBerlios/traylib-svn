# !/bin/sh

javac -classpath $PWD/../trayicon.jar:.   Tray.java

java -classpath $PWD/../trayicon.jar:. -Djava.library.path=$PWD/../  Tray

