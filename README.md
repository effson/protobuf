# protobuf
Protobuf（全称：Protocol Buffers）是由 Google 开发的一种轻量级、高效、可扩展的结构化数据序列化协议，常用于服务之间通信、数据存储等场景。<br>
可以把 Protobuf 看作是一种比 JSON、XML 更快、更省空间的“数据格式”或“传输协议”。<br>
<br>
1.安装protoc<br>
git clone https://github.com/protocolbuffers/protobuf.git<br>
cd protobuf<br>
git checkout v21.12  # 选择版本<br>
./autogen.sh<br>
./configure<br>
make -j$(nproc)<br>
sudo make install<br>
<img width="281" alt="image" src="https://github.com/user-attachments/assets/793acded-72f3-4152-b51b-a809df1b0ac3" /><br>
<br>
2.编译.proto文件<br>
protoc --cpp_out=. addressbook.proto<br>
生成.pb.h和.pb.cc文件<br>
<img width="400" alt="image" src="https://github.com/user-attachments/assets/eae79c98-58a2-4831-ad63-afe68278db0a" /><br>
<br>
3.编译list_people.cc和add_people.cc<br>
g++ -std=c++11 -I/usr/local/include -L/usr/local/lib add_people.cc addressbook.pb.cc -o add_people -lprotobuf -lpthread<br>
g++ -std=c++11 -I/usr/local/include -L/usr/local/lib list_people.cc addressbook.pb.cc -o list_people -lprotobuf -lpthread<br>
<img width="754" alt="image" src="https://github.com/user-attachments/assets/890cf3de-ce3b-4dcb-b691-d12d9f418e33" /><br>
<br>
<img width="386" alt="image" src="https://github.com/user-attachments/assets/ad2a44e3-cecf-42cc-9f9b-77a8ecab9692" /><br>
<img width="356" alt="image" src="https://github.com/user-attachments/assets/9a5c8567-7280-44fe-8f92-551b2f2d50b6" /><br>
