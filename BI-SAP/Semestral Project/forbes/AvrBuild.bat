@ECHO OFF
"C:\Program Files (x86)\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "H:\avrstudio\forbes\labels.tmp" -fI -W+ie -C V2E -o "H:\avrstudio\forbes\forbes.hex" -d "H:\avrstudio\forbes\forbes.obj" -e "H:\avrstudio\forbes\forbes.eep" -m "H:\avrstudio\forbes\forbes.map" "H:\avrstudio\forbes\forbes.asm"
