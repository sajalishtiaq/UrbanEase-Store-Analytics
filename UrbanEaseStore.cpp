#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cmath>
using namespace std;

struct SalesRecord
{
	char* date;
	char* time;
	double amount;
};
struct Centroid 
{
    double total_sales;
    double num_customers;
    double profit;
};

struct Product
{
	char* SKU;
	char* name;
	double price;
	SalesRecord* sales[24];
};

struct Location
{
	double lat;
	double lon;
};

struct Employee
{
	int id;
	char* name;
	int salary;
};

struct Store
{
	int id;
	char* name;
	Location loc;
	Employee manager;
	Employee staff[3];
	double mon_cost;
    Product* products;
    int pro_count;
    int customer_count[24];
	double total_sales[24];
    double growthRate;
    double forecast;
    double confidence;
};
void generateData(Store*& stores, int total) 
{
    srand(time(0));
    const char* store_names[]={"UrbanEase", "Retailbrand", "FashionClub", "Elitefashion", "TrendySpot"};
    const char* manager_names[]={"Salman Ahmed", "Alyan Ahmed", "Ahmed Ali", "Ashfaq Ahmed", "Muhammad Ali"};
    const char* staff_names[]={"Ali khan", "Muhammad Hamza", "Bilal Ahmed", "Usman Mughal", "Asad Abdur Rehman","Mardan Shah", "Arsalan Khan", "Daniyal Munir", "Hammad Gondal", "Junaid Sheikh"};
    const char* dates[]={"01-2022", "02-2022", "03-2022", "04-2022", "05-2022", "06-2022", "07-2022", "08-2022", "09-2022", "10-2022", "11-2022", "12-2022"};
    const char* times[]={"08:00AM", "10:54AM", "01:36PM", "02:52PM", "03:44PM", "04:12PM", "05:27PM", "06:30PM", "07:09PM", "08:29PM", "09:16PM", "10:49PM"};
    int num_products=0;
    while (num_products<=0) 
	{
        cout<<"Enter the Total Number of Products: ";
        cin>>num_products;
        if (num_products<=0) 
		{
			cout<<"Invalid Input!\n";
		}
    }
    stores=new Store[total];
    
    for (int i=0;i<total;i++)
	{
        int store_index=rand()%5;
        stores[i].name=strdup(store_names[store_index]);
        stores[i].id=i+1;
        stores[i].loc={(rand()%18000-9000)/100.0,(rand()%18000-9000)/100.0};
        stores[i].mon_cost=rand()%800000+200000;
        stores[i].pro_count=num_products;
        int manager_index=rand()%5;
        stores[i].manager={rand()%100+1,strdup(manager_names[manager_index]),rand()%80000+20000};
        for (int j=0;j<3;j++) 
		{
            int staff_index=rand()%10;
            stores[i].staff[j]={rand()%100+1,strdup(staff_names[staff_index]),rand()%25000+5000};
        }
		stores[i].products=new Product[num_products];
        for (int j=0;j<num_products;j++) 
		{
            stores[i].products[j].SKU=new char[6];
            stores[i].products[j].SKU[0]='A'+rand()%26;
            for (int k=1;k<5;k++) 
            {
                stores[i].products[j].SKU[k]='0'+rand()%10;	
			}
            stores[i].products[j].SKU[5]='\0';
            stores[i].products[j].name=new char[5];
            for (int k=0;k<4;k++)
            {
                stores[i].products[j].name[k]='A'+rand()%26;
			}
            stores[i].products[j].name[4]='\0';
            stores[i].products[j].price=rand()%9000+1000;
            for (int k=0;k<24;k++) 
			{
                stores[i].products[j].sales[k]=new SalesRecord;
                stores[i].products[j].sales[k]->date=strdup(dates[k % 12]);
                stores[i].products[j].sales[k]->time=strdup(times[k % 12]);
                stores[i].products[j].sales[k]->amount=stores[i].products[j].price;
            }
        }
        for (int j=0;j<24;j++) 
		{
            stores[i].customer_count[j]=rand()%800+200;
            stores[i].total_sales[j]=rand()%100000+50000;
        }
    }
}    
void save(Store* stores,int total) 
{
   ofstream file("Stores_data.txt");
   for (int i=0;i<total;i++)
   {
		file<<"Store ID: "<<stores[i].id<<endl;
		file<<"Store Name: "<<stores[i].name<<endl;
		file<<"Store Monthly Cost: "<<stores[i].mon_cost<<endl;
		file<<"Store's Geo Coordinates: "<<endl;
		file<<"Latitude: "<<stores[i].loc.lat<<endl;
		file<<"Longitude: "<<stores[i].loc.lon<<endl<<endl;
		file<<"Store's Manger: "<<endl;
		file<<"ID:"<<stores[i].manager.id<<endl;
		file<<"Name: "<<stores[i].manager.name<<endl;
		file<<"Salary: "<<stores[i].manager.salary<<endl<<endl;
		file<<"Store's Staff: "<<endl;
		for (int j=0;j<3;j++)
		{
			file<<"Staff "<<j+1<<endl;
			file<<"ID: "<<stores[i].staff[j].id<<endl;
			file<<"Name: "<<stores[i].staff[j].name<<endl;
		 	file<<"Salary: "<<stores[i].staff[j].salary<<endl;
		}
		file<<endl;
		file<<"Total Number of products: "<<stores[i].pro_count<<endl;	
		for(int j=0;j<stores[i].pro_count;j++)
		{
           file<<"Product Name: "<<stores[i].products[j].name<<" -- SKU: "<<stores[i].products[j].SKU<<" -- "<<" -- Unit Price: "<<stores[i].products[j].price<<" --"<<endl<<endl;
            for(int l=0;l<24;l++) 
			{
				
                file<<" -- Month: -- "<<stores[i].products[j].sales[l]->date<<" -- Time: "<<stores[i].products[j].sales[l]->time<<" -- Sales: "<<fixed<<stores[i].products[j].sales[l]->amount<<" -- "<<endl;
            }
            file<<endl;
        }
	}
   file.close();
}
void updatecost(Store* stores,int id,int total) 
{
	for (int i=0;i<total;i++)
	{
		if (stores[i].id==id)
		{
		    cout<<"Enter new monthly cost for Store "<<id<<": ";
		    cin>>stores[i].mon_cost;
		    cout<<"Cost updated successfully!"<<endl;
		}
	}
	save(stores,total);
}

void clusterStores(Store* stores,int total) 
{
    const int loc_cluster=3;
    const int perf_cluster=3;
    const double min=0.001;
    ofstream file("cluster_stores.txt");
    if (!file.is_open()) 
	{
        cerr<<"Error opening output file!"<<endl;
        return;
    }
	Location* loc=new Location[loc_cluster];
    int* loc_assign=new int[total];
    for(int i=0;i<loc_cluster;i++) 
	{
        int index=rand()%total;
        loc[i]=stores[index].loc;
    }

    bool changed;
    do 
	{
        changed=false;
		for(int i=0;i<total;i++) 
		{
            double min_distance=INFINITY;
            int new_cluster=-1;
            for(int j=0;j<loc_cluster;j++) 
			{
                double dx=stores[i].loc.lat-loc[j].lat;
                double dy=stores[i].loc.lon-loc[j].lon;
                double dist=sqrt(dx*dx+dy*dy);
                if(dist<min_distance) 
				{
                    min_distance=dist;
                    new_cluster=j;
                }
            }
            if (loc_assign[i]!=new_cluster) 
			{
                loc_assign[i]=new_cluster;
                changed=true;
            }
        }
        Location* new_loc=new Location[loc_cluster]();
        int total_clusters[loc_cluster]={0};
        for(int i=0;i<total;i++) 
		{
            int cluster=loc_assign[i];
            new_loc[cluster].lat+=stores[i].loc.lat;
            new_loc[cluster].lon+=stores[i].loc.lon;
            total_clusters[cluster]++;
        }

        double max_change=0;
        for(int j=0;j<loc_cluster;j++) 
		{
            if(total_clusters[j]>0) 
			{
                Location old=loc[j];
                loc[j].lat=new_loc[j].lat/total_clusters[j];
                loc[j].lon=new_loc[j].lon/total_clusters[j];

                double change=sqrt(pow(old.lat-loc[j].lat,2)+pow(old.lon-loc[j].lon,2));
                max_change=max(max_change,change);
            }
        }

        changed=(max_change>min);
        delete[] new_loc;
    } while(changed);
    file<<"------------- Store Clustering Report -------------"<<endl<<endl;

    file<<"Primary Geographic Clusters:"<<endl;
    for(int g=0;g<loc_cluster;g++) 
	{
        int count=0;
        for(int i=0;i<total;i++) 
        {
        	if(loc_assign[i]==g) 
        	{
        	    count++;	
			}
            
		}
           

        file<<"Cluster "<<g+1<<":"<<endl;
        file<<"  Centroid: ("<<fixed<<setprecision(4)<<loc[g].lat<<", "<<loc[g].lon<<")"<<endl;
        file<<"  Stores: "<<count<<endl<<endl;
    }
    file<<endl<<"Secondary Performance Clustering:"<<endl;
    for(int g=0;g<loc_cluster;g++) 
	{
        int cluster_size=0;
        for(int i=0;i<total;i++)
		{ 
            if(loc_assign[i]==g) 
            {
            	cluster_size++;
			}
		}
        Store** cluster_stores=new Store*[cluster_size];
        Centroid* centroids=new Centroid[perf_cluster];
        int* perf_assign=new int[cluster_size];

        int index=0;
        for(int i=0;i<total;i++) 
		{
            if(loc_assign[i]==g) 
			{
                cluster_stores[index++]=&stores[i];
            }
        }
        double** features=new double*[cluster_size];
        for(int i=0;i<cluster_size;i++) 
		{
            features[i]=new double[3];
            features[i][0]=0;
            for(int h=0;h<24;h++) 
            {
                features[i][0]+=cluster_stores[i]->total_sales[h];	
			}
            features[i][1]=0;
            for(int h=0;h<24;h++)
			{
			    features[i][1]+=cluster_stores[i]->customer_count[h];
			}
            features[i][2]=features[i][0]-cluster_stores[i]->mon_cost;
        }
		for(int p=0;p<perf_cluster;p++) 
		{
            int random=rand()%cluster_size;
            centroids[p]={features[random][0],features[random][1],features[random][2]};
        }
        bool perf_changed;
        do {
            perf_changed=false;

            for(int i=0;i<cluster_size;i++) 
			{
                double min_distance=INFINITY;
                int new_cluster=-1;
                for(int p=0;p<perf_cluster;p++) 
				{
                    double dist=pow(features[i][0]-centroids[p].total_sales,2)+pow(features[i][1]-centroids[p].num_customers,2)+pow(features[i][2]-centroids[p].profit,2);
                    if(dist<min_distance) 
					{
                        min_distance=dist;
                        new_cluster=p;
                    }
                }
                if(perf_assign[i]!=new_cluster) 
				{
                    perf_assign[i]=new_cluster;
                    perf_changed=true;
                }
            }
            Centroid new_centroids[perf_cluster]={0};
            int per_count[perf_cluster]={0};
            for(int i=0;i<cluster_size;i++) 
			{
                int cluster=perf_assign[i];
                new_centroids[cluster].total_sales+=features[i][0];
                new_centroids[cluster].num_customers+=features[i][1];
                new_centroids[cluster].profit+=features[i][2];
                per_count[cluster]++;
            }

            double max_change=0;
            for(int p=0;p<perf_cluster;p++) 
			{
                if(per_count[p]>0) 
				{
                    Centroid old=centroids[p];
                    centroids[p].total_sales=new_centroids[p].total_sales/per_count[p];
                    centroids[p].num_customers=new_centroids[p].num_customers/per_count[p];
                    centroids[p].profit=new_centroids[p].profit/per_count[p];
                    double change=sqrt(pow(old.total_sales-centroids[p].total_sales,2)+pow(old.num_customers-centroids[p].num_customers,2)+pow(old.profit-centroids[p].profit,2));
                    max_change =max(max_change,change);
                }
            }
            perf_changed=(max_change>min);
        } while(perf_changed);
        delete[] cluster_stores;
        delete[] centroids;
        delete[] perf_assign;
        for(int i=0;i<cluster_size;i++) 
		{
			delete[] features[i];
		}
        delete[] features;
    }

    delete[] loc;
    delete[] loc_assign;
    file.close();

    cout<<"Clustered stores data saved to ''cluster_stores.txt'"<<endl;
}

double calculateTotalSales(const Store& store) 
{
    double total=0;
    for(int i=0;i<24;i++) 
	{
        total+=store.total_sales[i];
    }
    return total;
}

double calculateGrowthRate(const Store& store) 
{
    double first_year=0,second_year=0,a;
    for(int i=0;i<12;i++) 
	{
        first_year+=store.total_sales[i];
        second_year+=store.total_sales[i+12];
    }
    a=((second_year-first_year)/(first_year!=0?first_year:1))*100;
    return a;
}
void predictSales(Store* stores,int total)
{
	ofstream file("sales_forecast.txt");
    file<<"Sales Forecast:\n\n";
    for(int i=0;i<total;i++) 
	{
        double growth=1.0+(calculateGrowthRate(stores[i])/100.0);
    }
    for(int i=0;i<total;i++) 
	{
		double sum=0;
		
        for(int j=18;j<24;j++) 
		{
            sum+=stores[i].total_sales[j];
        }
        
        double avg=sum/6;
        double variance=0;
        
        for(int j=18;j<24;j++) 
		{
            variance+=pow(stores[i].total_sales[j]-avg,2);
        }
        
        double stddev=sqrt(variance/6);
        double confidence=95.0-(stddev/avg)*100.0;
        
        if(confidence<80.0)
		{
			confidence=80.0;
		}
        if(confidence>99.9)
        {
        	confidence=99.9;
		}
        
        file<<"Store "<<i+1<<" ("<<stores[i].name<<endl;
		//file<<"Forecast: $"<<fixed<<setprecision(6)<<(avg*growth*12)<<endl;
		file<<"Confidence: "<<fixed<<setprecision(6)<<confidence<<"%"<<endl;
    }
    
    cout<<"The Future Forecast is stored in 'sales_forecast.txt'."<<endl;
    file.close();
}

void generateReport(Store* stores,int total)
{
	Store** sortedStores=new Store*[total];
	
    for(int i=0;i<total;i++) 
	{
        sortedStores[i]=&stores[i];
    }

    for(int i=0;i<total-1;i++) 
	{
        int maxIdx=i;
        
        for(int j=i+1;j<total;j++) 
		{
            if(calculateTotalSales(*sortedStores[j])>calculateTotalSales(*sortedStores[maxIdx])) 
			{
                maxIdx=j;
            }
        }
        if(maxIdx!=i) 
		{
            Store* temp[i];
            sortedStores[i]=sortedStores[maxIdx];
            sortedStores[maxIdx]=temp[i];
        }
    }

    ofstream file("performance_report.txt");
    file<<"Performance Report"<<endl<<endl<<"Top 10 Stores:"<<endl;
    for(int i=0;i<10&&i<total;i++) 
	{
        Store* s=sortedStores[i];
        file<<i+1<<". "<<s->name<<" (ID: "<<s->id<<")"<<endl;
    	file<<"Total Sales: $"<<fixed<<setprecision(0)<<calculateTotalSales(*s)<<endl;
		file<<"Growth Rate: "<<fixed<<setprecision(6)<<calculateGrowthRate(*s)<<"%"<<endl<<endl;
    }

    file<<endl<<"Bottom 5 Stores:"<<endl;
    for(int i=total-5;i<total;i++) 
	{
        Store* s=sortedStores[i];
        file<<total-i<<". "<<s->name<<" (ID: "<<s->id<<")"<<endl;
    	file<<"Total Sales: $"<<fixed<<setprecision(0)<<calculateTotalSales(*s)<<endl;
        file<<"Growth Rate: "<<fixed<<setprecision(6)<<calculateGrowthRate(*s)<<"%"<<endl<<endl;
    }
    
    file.close();
    delete[] sortedStores;
}

void showGraph(Store* stores,int total) 
{
    cout<<"Bar Graph For Sales Trends: "<<endl;
    for (int month=0;month<24;month++) 
	{
        double max_sales=0.0;
        
        for (int i=0;i<total;i++) 
		{
            if (stores[i].total_sales[month]>max_sales) 
			{
                max_sales=stores[i].total_sales[month];
            }
        }
        if (max_sales>0) 
		{
            cout<<endl<<"Month "<<month+1<<" (Max: $"<<max_sales<<")"<<endl;\
            int stores_to_show;
			if (total<10)
			{
				stores_to_show=total;
			} 
			else
			{
				stores_to_show=10;
			} 
			
            for (int i=0;i<stores_to_show;i++) 
			{
                int bar_width=static_cast<int>((stores[i].total_sales[month]/max_sales)*20);
                cout<<stores[i].name<<" |";
                
                for (int b=0;b<bar_width;b++) 
				{
                    cout<<"#";
                }
                cout<<" $"<<static_cast<int>(stores[i].total_sales[month]/1000)<<"K"<<endl;
            }
        }
    }
}


void deallocate(Store*& stores, int total)
{
	for (int i=0;i<total;i++)
	{
		delete[] stores[i].name;
		delete[] stores[i].manager.name;
		
    	for (int j=0;j<3;j++) 
		{
	        delete[] stores[i].staff[j].name;
	    }
	    
	    for (int j=0;j<stores[i].pro_count;j++) 
		{
	        delete[] stores[i].products[j].SKU;
	        delete[] stores[i].products[j].name;
	        
	        for (int k=0;k<24;k++) 
			{
	            if (stores[i].products[j].sales[k]) 
				{
	                delete[] stores[i].products[j].sales[k]->date;
	                delete[] stores[i].products[j].sales[k]->time;
	                delete stores[i].products[j].sales[k];
	            }
	        }
	    }
	    
    	delete[] stores[i].products;
	}
}


int main ()
{
	
	int choice,id,total=100;
	bool flag=true;
	Store* stores;
	cout<<endl<<"-----------------UrbanEase: Store Analytics and Advanced Management System-----------------"<<endl<<endl;
	do 
	{
		cout<<"1. Generate Data. "<<endl;
		cout<<"2. Update Cost. "<<endl;
		cout<<"3. Print the Clustered data. "<<endl;
		cout<<"4. Print Future Forecast of Sores. "<<endl;
		cout<<"5. Generate Data Analytical Report. "<<endl;
		cout<<"6. Print Bar Graph. "<<endl;
		cout<<"7. Exit."<<endl;
		cout<<"Enter Your Choice: ";
		cin>>choice;
		switch (choice)
		{
			case 1:
				{
					generateData(stores, total);
					save(stores, total);
					cout<<"The Data For 100 Stores is generated in file 'Stores_Data.txt' "<<endl;
					break;	
				}
			case 2:
				{
					cout<<"Enter the Id of store you want to update: ";
					cin>>id;
					if (id < 1 || id > 100)
					{
						cout<<"Invalid Input!! Enter Again: ";
						cin>>id;
					}
                	else 
					{
						updatecost(stores, id, total);
					}
					break;	
				}
			case 3:
				{
					clusterStores(stores, total);
					break;	
				}
			case 4:
				{
					predictSales(stores, total);
					break;	
				}
			case 5:
				{
					generateReport(stores, total);
					break;	
				}
			case 6:
				{
					showGraph(stores, total);
					break;	
				}
			case 7:
				{
					cout<<"Exiting the program........."<<endl;
					flag=false;
					break;	
				}
			default:
				{
					cout<<"Invalid Input!!"<<endl;	
				}
		}
	} while (flag);
	deallocate(stores, total);
	return 0;
	
}
