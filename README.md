# u-boot-2013.01.01
for tq210

编译
make CROSS_COMPILE=arm-none-linux-gnueabi- distclean(清除以前的编译文件，首次编译不用执行)
make CROSS_COMPILE=arm-none-linux-gnueabi- s5p_goni_config
make CROSS_COMPILE=arm-none-linux-gnueabi-
备份
make backup

制作SD启动卡
fdisk -l(查看SD卡的设备名)
dd bs=512 seek=1 if=/dev/zero of=/dev/sdb count=2048
dd iflag=dsync oflag=dsync if=spl/goni-spl.bin of=/dev/sdb seek=1
dd iflag=dsync oflag=dsync if=u-boot.bin of=/dev/sdb seek=49
