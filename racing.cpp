//car racing predection:::
#include<iostream>
#include<list>
#include<ctime>
#include<vector>
#include<thread>
#include<chrono>
using namespace std::chrono_literals;
class loading{
    public:
        std::string name;
        int count;
        loading(std::string name,int count)
        {
            this->count=count;
            this->name=name;
        }
        loading():name(" "),count(0){}
        loading(const loading &copy)
        {
            name=copy.name;
            count=copy.count;
        }
    bool operator==(const loading &object)const
    {
        return name==object.name;
    }

};
std::ostream &operator<<(std::ostream &COUT,loading &object)
{
    COUT<<object.name<<' '<<object.count<<std::endl;
    return COUT;
}
class temp{
    static int count;
    int choose;
    public:
    std::list<loading> mem;
    void operator +=(loading &object)
    {
        count ++;
        this->mem.push_back(object);
    }
    void total()
    {
        std::cout<<count<<std::endl;
    }
    void operator -=(loading &object)
    {
        count--;
        this->mem.remove(object);
    }
};
std::ostream &operator <<(std::ostream &COUT,temp obj)
{
    for(loading i: obj.mem)
    {
        COUT<<i;
    }
    return COUT;
}
int n=0,choose;
void rendering(std::vector<loading>&,temp&);
int temp::count;
void Cases(std::vector<loading>&,temp &);
int main()
{
   int play=0;
    temp obj;
    std::vector<loading> object={
        loading("Lambo",1),
        loading("ferari",2),
        loading("Bugarti",3),
        loading("supra",4),
        loading("corvet",5),
        loading("mclaren",6)
    };
    for(loading i:object)
    {
        obj+=i;
    }
    std::cout<<"The total particapant is - ";obj.total();
   std::cout<<obj;
    std::cout<<'\n'<<std::endl;
    std::cout<<"Press Y to add custom car or any key to continue.."<<std::endl;
   char c=getchar();
  
   if(toupper(c)=='Y')
   {
        Cases(object,obj);
        for(loading i:object)
        {
            obj+=i;
        }
        std::cout<<"The total particapant is - ";obj.total();
        std::cout<<obj;
        std::cout<<'\n'<<std::endl;
   }
    int win=2000;
    int loose=1000;
    int wallet=3000;
  
    
    std::cout<<"Enter your choise id car-";
    std::cin>>choose;
        rendering(object,obj);

        std::cout<<"your wallet is "<<wallet<<'$'<<" your choise ID- "<<choose<<std::endl;
        auto ptr=obj.mem.begin();//this is the pointer which points to the first value so only begin
        loading Win=*ptr;//accessing the value of the address and copy to the object ::
        if(choose==Win.count)
        {
            std::cout<<"You won "<<win<<'$'<<std::endl;
            wallet+=win;
        }
        else{
            std::cout<<"You lost "<<loose<<'$'<<std::endl;
            wallet-=loose;
        }
        std::cout<<"#1car is  "<<std::endl;
        std::cout<<obj; //overloaded::
        std::cout<<"\nTotal time taken is "<<n<<" sec"<<std::endl;
    std::cout<<"money- "<<wallet<<'$'<<std::endl;
    return 0;
}
void rendering(std::vector<loading>&object,temp &obj)
{
    system("cls");


     srand(time(NULL));
     //defining the lamda::and taking the  variable as the object1 size
    auto guess=[object](){
        return rand()%object.size();
    };
    int hold;
    
    //game loop hold for temporary holding the guess of the game;
    std::cout<<"Time frame.. ";
    do{
        hold=guess();
       
        obj-=object[hold];
        std::this_thread::sleep_for(1000ms);
        std::cout<<++n<<'.';
        
    }while(obj.mem.size()!=1);
    std::cout<<std::endl;
}

void Cases(std::vector<loading>&object,temp &obj)
{
        for(loading i:object)
        {
            obj-=i;
        }
     char c;
    std::string name;
    int id=6;
    do{
        
      std::cout<<"press e to end selection...and y to continue>>>"<<std::endl;
       std::cin>>c;
        switch (c)
        {
            case 'y':
                id++;
                std::cout<<"Car-";
                std::cin>>name;
                object.push_back(loading(name,id));
                break;
            case 'e':
                std::cout<<"Confirmed"<<std::endl;
                break;
            default:
                std::cout<<"Invalid entry;;"<<std::endl;
        }

    }while(c!='e');
}