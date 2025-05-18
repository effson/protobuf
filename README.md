# protobuf


1.安装protoc
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git checkout v21.12  # 选择版本
./autogen.sh
./configure
make -j$(nproc)
sudo make install
<img width="281" alt="image" src="https://github.com/user-attachments/assets/793acded-72f3-4152-b51b-a809df1b0ac3" />

2.编译.proto文件
protoc --cpp_out=. addressbook.proto
生成.pb.h和.pb.cc文件
<img width="400" alt="image" src="https://github.com/user-attachments/assets/eae79c98-58a2-4831-ad63-afe68278db0a" />

3.编译list_people.cc和add_people.cc
g++ -std=c++11 -I/usr/local/include -L/usr/local/lib add_people.cc addressbook.pb.cc -o add_people -lprotobuf -lpthread
g++ -std=c++11 -I/usr/local/include -L/usr/local/lib list_people.cc addressbook.pb.cc -o list_people -lprotobuf -lpthread
<img width="754" alt="image" src="https://github.com/user-attachments/assets/890cf3de-ce3b-4dcb-b691-d12d9f418e33" />

<img width="386" alt="image" src="https://github.com/user-attachments/assets/ad2a44e3-cecf-42cc-9f9b-77a8ecab9692" />
<img width="356" alt="image" src="https://github.com/user-attachments/assets/9a5c8567-7280-44fe-8f92-551b2f2d50b6" />
