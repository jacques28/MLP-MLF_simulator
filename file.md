Step 1:
From kernel.org, download the latest kernel into one of your user directories using
wget url

Step 2:
Untar using
tar xvf linux-xx.xx.xx.tar.gz

Step 3:
Copy existing configuration
cd linux-xx.xx.xx
cp -v /boot/config-$(uname -r) .config

Step 4:
Install required packages
sudo apt install build-essential libncurses5-dev bison flex libssl-dev libelf-dev

Step 5:
Configure
yes "" | make oldconfig
OR
make menuconfig
OR
make xconfig
OR
make gconfig

Step 5.1:
Open .config in vi

Replace the line 

CONFIG_SYSTEM_TRUSTED_KEYS="debian/canonical-certs.pem"  
with

CONFIG_SYSTEM_TRUSTED_KEYS="" 
Also, Replace the line 

CONFIG_SYSTEM_REVOCATION_KEYS="debian/canonical-certs.pem"  
with

CONFIG_SYSTEM_REVOCATION_KEYS="" 



Step 6:
Compile
make
OR
make -j #numberofcorestouse

Step 7:
Install modules
sudo make modules_install

Step 8:
Install the Linux kernel
sudo make install

