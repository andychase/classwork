cd /scratch/spring2016/
ls
mkdir cs444-017
ls
cd cs444-017
ls
git init
git clone git://git.yoctoproject.org/linux-yocto-3.14
git clone --depth 1 git://git.yoctoproject.org/linux-yocto-3.14 v3.14.26
ls
cd v3.14.26/
ls
source /scratch/opt/environment-setup-i586-poky-linux
less /scratch/opt/environment-setup-i586-poky-linux
make
make -j4 all
cp -r /scratch/spring2015/files/config-3.14.26-yocto-qemu .config
cd .config
ls
man cp
cp -r /scratch/spring2015/files/config-3.14.26-yocto-qemu .config/
cp -r /scratch/spring2015/files/config-3.14.26-yocto-qemu .config
less .config
make -j4 all
make clean
make -j4 all
exit
ssh chasean@os-class.engr.oregonstate.edu
exit
ls
echo "cd /scratch/spring2016/cs444-017" > os
chmod a+x os
./os
ls
. os
ls
cd
ls
ls -a
vi .profile
vi .bash_profile 
vi .bashrc
exit
vi .bashr
vi .bashrc
exit
ssh chasean@os-class.engr.oregonstate.edu
. os
ls
vi start-qemu
# qemu-system-i386 -gdb tcp::5517 -S -nographic -kernel arch/x86/boot/bzImage -drive file=core-image-lsb-sdk-qemux86.ext3,if=virtio -enable-kvm -net none -usb -localtime --no-reboot --append "root=/dev/vda rw console=ttyS0 debug"
cp /scratch/spring2016/files/bzImage-qemux86.bin .
cp /scratch/spring2016/files/core-image-lsb-sdk-qemux86.ext3 .
ls
cd v3.14.26/
ls
cd kernel/
ls
cd ..
ls
less README 
cd kernel/
ls
cd ..
ls
less Kbuild 
less Makefile 
cd ..
ls
tree 
tree  > t
less t
cd v3.14.26/
ls
cd ..
ls
less t
rm t
mv start-qemu core-image-lsb-sdk-qemux86.ext3 bzImage-qemux86.bin v3.14.26/
ls
cd v3.14.26/
. start-qemu 
source /scratch/opt/environment-setup-i586-poky-linux
. start-qemu
ls
. os
cd v3.14.26/
. /scratch/opt/environment-setup-i586-poky-linux
$GDB 5517
man gdb
ls
echo $GDB
vi $GDB
vi `echo $GDB`
which `echo $GDB`
/scratch/opt/sysroots/x86_64-pokysdk-linux/usr/bin/i586-poky-linux/i586-poky-linux-gdb --help
gdb 127.0.0.1:5517 vmlinux
ls
gdb 127.0.0.1:5517 bzImage-qemux86.bin 
ls
gdb 127.0.0.1:5517 
gdb 127.0.0.1:5517 core-image-lsb-sdk-qemux86.ext3 
ls
$GDB 127.0.0.1:5517
$GDB 127.0.0.1:5517 bzImage-qemux86.bin 
vi start-qemu 
screen -R q
less
ps -u chasan
ps 
ps -u chasean
$GDB 127.0.0.1:5517 2018
. /scratch/opt/environment-setup-i586-poky-linux
$GDB 127.0.0.1:5517 2018
$GDB :5517 2018
$GDB 2018
$GDB 127.0.0.1:5517 
$GDB --help | less
ls
. os
ls
cd v3.14.26/
$GDB 127.0.0.1:5517 arch/x86/boot/bzImage 
$GDB
ps
ps -u chasean
kill 2018
exit
. start-qemu 
. /scratch/opt/environment-setup-i586-poky-linux
. start-qemu 
vi start-qemu 
. start-qemu 
exit
screen -r q
exit
