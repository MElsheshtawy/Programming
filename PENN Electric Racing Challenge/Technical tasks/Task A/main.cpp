#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main() {
    string myfile = R"(E:\working\College and Courses\UPENN\Penn electric racing\Application\Elsheshtawy_Mohamed_SoftwareChallengeSubmission\Technical tasks\Task A\TaskA.csv)";
    ifstream file(myfile);
    if (!file.is_open()) {
        cerr << "Error opening file: " << myfile << endl;
        return 1;
    }
    //cout<<1<<endl;  debugging
    map<int,int> CanId; // 1 = volt || 2 = ampere ||  3 =Front Left Wheel Speed ||
    // 4=Front Right Wheel Speed || 5 = Back Left Wheel Speed || 6 =  Back Right Wheel Speed
    string line;
    vector<vector<double>> dataofeverything(6,vector<double>(3*1e6));
    while (getline(file, line)) {
        //cout<<line<<endl;   debugging
        if(line[0] == 'P')continue;
        if(line[0] != 'V')break;
        stringstream ss(line);
        string value;
        bool goodval = false;
        int val = -1;
        vector<string> comparison ={"(ams.pack.voltage):","(ams.pack.current):","(pcm.wheelSpeeds.frontLeft):","(pcm.wheelSpeeds.frontRight):",
                                    "(pcm.wheelSpeeds.backLeft):","(pcm.wheelSpeeds.backRight):"};
        while (getline(ss, value, ' ')) {
            //cout<< value<< endl;  debugging
            if(goodval){
                goodval = false;
                CanId[stoi(value)] = val+1;
                break;
            }
            for(int i = 0;i<comparison.size();i++){
                int j=0;
                if(comparison[i].size()== value.size()) {
                    for (j = 0; j < comparison[i].size(); j++) {
                        if (comparison[i][j] != value[j])break;
                    }
                }
                if(comparison[i].size() == j){
                    val = i;
                    goodval = true;
                    break;
                }
            }
        }
    }
    /*
    for(auto it: CanId){
        cout<< it.first<< " "<< it.second<<endl;
    }
     */
    int defaulttime = 125000;
    do{
        if(line[0] != '#') {
            stringstream ss(line);
            string value;
            int time;
            int index;
            double data;
            //cout<< "###############"<<endl;
            for(int i = 0;i<3;i++){
                getline(ss, value, ',');
                //cout<<value<< " "<< i<< endl;
                if(i == 0){
                    time = stoi(value)-defaulttime;
                }
                else if(i == 1){
                    if(CanId[stoi(value)])
                        index = CanId[stoi(value)];
                    else
                        index = -1;
                }
                else{
                    data = stod(value);
                }
            }
            if(index == -1)continue;
            dataofeverything[index-1][time] = data;
            //cout<< index<< " "<< time<<  " "<< data<<endl;
        }
    }
    while(getline(file, line));
    double minimumspeed = INT64_MAX;double maximumspeed = 0; double power = 0;
    for(int j = 0;j<dataofeverything[0].size();j++){
        double speed = (dataofeverything[2][j] +dataofeverything[3][j])/2;//only the two front wheels becausethe back might
        //be spinning without moving so it isn't accurate
        if(speed){
            minimumspeed = min(minimumspeed,speed);
        }
        maximumspeed = max(maximumspeed,speed);
        if(j){ // if I had more time I would have done better numerical integration because this is awfulll :(
            double height = ((dataofeverything[0][j]+dataofeverything[0][j-1])/2)*((dataofeverything[1][j]+dataofeverything[1][j-1])/2);
            power+= height*0.001;
        }
    }
    cout<<"the minimum speed in MPH = " << minimumspeed<<endl;
    cout<<"the maximum speed in MPH= " << maximumspeed<<endl;
    cout<<"the Power using integraion in kWh= "<< power/(1000*60*60)<<endl;
    //cout<< 1111111<<endl;
    file.close();
    return 0;
}
