unzip SDL2-2.0.0.zip
cd SDL2-2.0.0
sudo ./configure
sudo make
sudo make install

cd ..

tar -vzxf SDL2_ttf-2.0.12.tar.gz
cd SDL2_ttf-2.0.12
sudo ./configure
sudo make
sudo make install

cd ..

tar -vzxf SDL2_net-2.0.0.tar.gz
cd SDL2_net-2.0.0
sudo ./configure
sudo make
sudo make install

cd ..

unzip SDL2_mixer-2.0.0.zip
cd SDL2_mixer-2.0.0
sudo ./configure
sudo make
sudo make install

cd ..

unzip SDL2_image-2.0.0.zip
cd SDL2_image-2.0.0
sudo ./configure
sudo make
sudo make install

cd ..

sudo ldconfig

cd warofthenets
sudo ./configure
sudo make
sudo make install

sudo rm -rf SDL2_ttf-2.0.12
sudo rm -rf SDL2-2.0.0
sudo rm -rf SDL2_net-2.0.0
sudo rm -rf SDL2_mixer-2.0.0
sudo rm -rf SDL2_image-2.0.0

