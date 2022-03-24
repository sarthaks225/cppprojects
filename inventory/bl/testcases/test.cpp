#include<iostream>
#include<bl/uommanager>
#include<dl/uomdao>
#include<stringutils>

using namespace inventory;
using namespace business_layer;
int main()
{
string title;
int ch;
UnitOfMeasurement uom;
forward_list<abc::IUnitOfMeasurement *> *list;
abc::IUnitOfMeasurement *iuom;
UnitOfMeasurementManager uommanager;
while(1)
{
cout<<endl;
cout<<"1. add uom "<<endl;
cout<<"2. get all "<<endl;
cout<<"3. update uom by using code and title"<<endl;
cout<<"4. exit"<<endl;
cout<<"enter your choice :";
cin>>ch;
if(ch==1)
{

cout<<"enter title: ";
cin>>title;

uom.setCode(0);
uom.setTitle(title);
try
{
uommanager.addUnitOfMeasurement(&uom);
cout<<uom.getTitle()<<" title added"<<endl;
}
catch (BLException blexc)
{
cout<<"some problem"<<endl;
if(blexc.hasGenericException())
{
cout<<blexc.getGenericException()<<endl;
}
if(blexc.hasPropertyException("code"))
{
cout<<blexc.getPropertyException("code")<<endl;
}
if(blexc.hasPropertyException("title"))
{
cout<<blexc.getPropertyException("title")<<endl;
}

}

}

if(ch==2)
{

try
{
list=uommanager.getAllUnitOfMeasurement();
while(list->begin()!=list->end())
{
cout<<"code : "<<(list->front())->getCode()<<", title: ("<<(list->front())->getTitle()<<")"<<endl;
list->pop_front();
}
}
catch(BLException blexc)
{

cout<<"some problem"<<endl;
if(blexc.hasGenericException())
{
cout<<blexc.getGenericException()<<endl;
}
if(blexc.hasPropertyException("code"))
{
cout<<blexc.getPropertyException("code")<<endl;
}
if(blexc.hasPropertyException("title"))
{
cout<<blexc.getPropertyException("title")<<endl;
}


}

}

if(ch==3)
{
cout<<"enter code to update title: ";
cin>>ch;
cout<<"enter new title : ";
cin>>title;
uom.setCode(ch);
uom.setTitle(title);
try
{
uommanager.updateUnitOfMeasurement(&uom);
cout<<"updattion done ...."<<endl;
}
catch(BLException blexc)
{

cout<<"some problem"<<endl;
if(blexc.hasGenericException())
{
cout<<blexc.getGenericException()<<endl;
}
if(blexc.hasPropertyException("code"))
{
cout<<blexc.getPropertyException("code")<<endl;
}
if(blexc.hasPropertyException("title"))
{
cout<<blexc.getPropertyException("title")<<endl;
}

}

}
if(ch==4) break;

}


cout<<"end of test"<<endl;
return 0;
}