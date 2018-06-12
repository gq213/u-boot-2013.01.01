# u-boot-2013.01.01
for tq210

编译
make CROSS_COMPILE=arm-buildroot-linux-gnueabihf- distclean(清除以前的编译文件，首次编译不用执行)
make CROSS_COMPILE=arm-buildroot-linux-gnueabihf- s5p_goni_config
make CROSS_COMPILE=arm-buildroot-linux-gnueabihf-
备份
make backup

制作SD启动卡
sudo fdisk -l(查看SD卡的设备名)
sudo dd bs=512 seek=1 if=/dev/zero of=/dev/sde count=2047
sudo dd iflag=dsync oflag=dsync if=spl/goni-spl.bin of=/dev/sde seek=1
sudo dd iflag=dsync oflag=dsync if=u-boot.bin of=/dev/sde seek=49
sudo sync
