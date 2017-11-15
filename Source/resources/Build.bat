bannertool.exe makebanner -i banner.png -a audio.wav -o banner.bnr
bannertool.exe makesmdh -s "CtrRGBPATTY" -l "CtrRGBPATTY" -p "CPunch" -i icon.png  -o icon.icn
makerom -f cia -o CtrRGBPATTY.cia -DAPP_ENCRYPTED=false -rsf CtrRGBPATTY.rsf -target t -exefslogo -elf CtrRGBPATTY.elf -icon icon.icn -banner banner.bnr