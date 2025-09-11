#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <cstring> // For memcpy

float bytesToFloat(const uint8_t bytes[4]) {
    float value;
    std::memcpy(&value, bytes, sizeof(value));
    return value;
}
using namespace std;
int main() {
    string myfile = R"(E:\working\College and Courses\UPENN\Penn electric racing\Application\Elsheshtawy_Mohamed_SoftwareChallengeSubmission\Technical tasks\Task B\TaskB.txt)";
    ifstream file(myfile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << myfile << endl;
        return 1;
    }
    //cout<<1<<endl;  //debugging

    map<int,int> CanId;
    CanId[311] = 1; //ampere
    CanId[313] = 2; //voltage
    CanId[222] = 3; //RPM

    string line;
    vector<vector<pair<double,int>>> dataofmessages(3);
    int defaulttime = 50354260;
    while (getline(file, line)) {
        //cout<<line<<endl;   //debugging
        if(line[0] == 'P')continue;
        stringstream ss(line);
        string value;
        int time=0;
        for(int i =0;i<2;i++){
            getline(ss, value, ':');
            //cout<<value<<endl;
            if(i == 0){
                time+=((value[0]-'0')*10 +(value[1]-'0'))*3600;
            }
            else time+= ((value[0]-'0')*10 +(value[1]-'0'))*60;
        }
        //cout<<0<<endl;
        getline(ss, value, ' ');
        //cout<<value<<endl;
        time*=1000;
        //time+= stod(value)*1000;   a lot of problems so I will handle it manually
        time+= (value[0]-'0')*100000+(value[1]-'0')*10000+(value[2]-'0')*1000+(value[3]-'0')*100+(value[4]-'0')*10;
        time-=defaulttime;
        //cout<<time<<value<< endl;
        // we finished getting the time

        getline(ss, value, ' ');
        //cout<<value<<endl;
        if(!(value[0]>='0' && value[0]<='9'))continue;
        //cout<<value<<endl;
        int ID = (value[0]-'0')*100;
        getline(ss, value, ' ');
        //cout<<value[2]<<endl;
        //cout<<value[value.size()-1]<<endl;
        //cout<<value<<endl;
        if(value.size()<4)continue;
        if(!(value[2]>='0' && value[2]<='9'&&value[3]>='0' && value[3]<='9'))continue;
        //cout<<value[2]<< " " << value[3]<<endl;
        ID+=10*(value[2]-'0');
        ID+= (value[3]-'0');
        //cout<<1<<endl;
        ID =CanId[ID];
        if(!ID) continue;
        //cout<<ID<<endl;
        getline(ss, value, ' ');
        //cout<<value<<endl;
        int size = value[0]-'0';
        //cout<<size<<" 0000"<<endl;
        if(size <4)continue;
        getline(ss, value, ' ');
        //cout<<value<<endl;

        vector<uint8_t >nums;
        for(int i =0;i<size-1;i++){
            getline(ss, value, ',');
            nums.push_back(stoi(value));
        }
        //cout<<2<<endl;
        getline(ss, value, ']');
        //cout<<value<<endl;
        nums.push_back(stoi(value));
        uint8_t data[4] = {nums[0], nums[1], nums[2], nums[3]};
        float firstnum = bytesToFloat(data);
        float secondnum = -1;
        if(nums.size()>4){
            data[0] = nums[4],data[1]= nums[5],data[2]= nums[6],data[3]= nums[7];
            secondnum = bytesToFloat(data);
            firstnum+=secondnum;
            firstnum/=2;
        }
        //cout<<3<<endl;
        if((ID == 1 && firstnum>600) ||(ID == 2 && firstnum>600) || (ID == 3 && firstnum>1600))continue;
        dataofmessages[ID-1].emplace_back(firstnum,time);
        //cout<<ID<< " " << time<< " " << firstnum<<endl;
    }
    //cout<<1<<endl;
    double minimumspeed = INT64_MAX;double maximumspeed = 0; double power = 0;
    for(int j = 0;j<min(dataofmessages[0].size(),dataofmessages[1].size());j++){
        if(j){ // not the best way for numerical integration but I didn't have enough time to fine tune it sorryyy
            double height = ((dataofmessages[0][j].first+dataofmessages[0][j-1].first)/2)*((dataofmessages[1][j].first+dataofmessages[1][j-1].first)/2);
            power+= (height/1000)*max((dataofmessages[0][j].second-dataofmessages[0][j-1].second),(dataofmessages[1][j].second-dataofmessages[1][j-1].second));
        }

    }
    long long average =0;
    for(int i = 0;i<dataofmessages[2].size();i++){
        if(dataofmessages[2][i].first>0) {
            minimumspeed = min(minimumspeed, dataofmessages[2][i].first);
            maximumspeed = max(maximumspeed,dataofmessages[2][i].first);
            average+=dataofmessages[2][i].first;
        }
    }
    average/= dataofmessages[2].size();
    cout<<"the minimum speed in MPH = " << minimumspeed*0.06096<<endl;
    cout<<"the maximum speed in MPH= " << maximumspeed*0.06096<<endl;
    cout<<"the average speed in MPH= " << average*0.06096<<endl;
    cout<<"the Power using integraion in kWh= "<< power/(1000*60*60)<<endl;
    //cout<< 1111111<<endl;
    file.close();
    return 0;
}
