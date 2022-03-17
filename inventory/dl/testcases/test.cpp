#include<iostream>
#include<uomdao>
#include<daoexception>
#include<uom>
using namespace inventory;
using namespace data_layer;
using namespace std;
int main()
{
UnitOfMeasurement m;
m.setTitle("kiLlo");
UnitOfMeasurementDAO uom;
try
{
uom.add(&m);
cout<<"Unit of measurement add with code: "<<(m.getCode())<<endl;
} catch(DAOException daoExc)
{
cout<<"daoexc"<<endl;
cout<<daoExc.what()<<endl;
}

return 0;
}