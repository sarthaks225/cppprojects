#include<iostream>
#include<dl/uomdao>
#include<dl/daoexception>
#include<dl/uom>
#include<forward_list>
using namespace inventory;
using namespace data_layer;
using namespace std;
int main()
{
int ch,i;
UnitOfMeasurement m;
UnitOfMeasurementDAO uomdao;
abc::IUnitOfMeasurement *iuom;
string title;
while(1)
{
cout<<"1. add unit of measurement"<<endl;
cout<<"2. get all/view all"<<endl;
cout<<"3. get by code"<<endl;
cout<<"4. get by title"<<endl;
cout<<"5. code exists"<<endl;
cout<<"6. title existd"<<endl;
cout<<"7. update"<<endl;
cout<<"8. remove"<<endl;
cout<<"9. exit"<<endl;
cout<<"enter your choice: ";
cin>>ch;
if(ch==1)
{
try
{
string title;
cout<<"enter string: ";
cin>>title;
m.setTitle(title.c_str());
uomdao.add(&m);
cout<<"Unit of measurement add with code: "<<(m.getCode())<<endl;
} catch(DAOException daoExc)
{
cout<<"daoexc"<<endl;
cout<<daoExc.what()<<endl;
}
}
if(ch==2)
{
try
{
forward_list<abc::IUnitOfMeasurement *> *list;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
list=(uomdao.getAll());
i=list->begin();
while(i!=list->end())
{
iuom=*i;
cout<<"code: "<<iuom->getCode()<<", Title: "<<iuom->getTitle()<<endl;
++i;
}
}
catch (DAOException daoExc)
{
cout<<daoExc.what()<<endl;
}

}

if(ch==3) 
{
cout<<"enter code: ";
cin>>i;
try
{
iuom=(uomdao.getByCode(i));
cout<<"code: "<<iuom->getCode()<<", title: "<<iuom->getTitle()<<endl;
} catch (DAOException daoExc)
{
cout<<daoExc.what()<<endl;
}


}

if(ch==4)
{
cout<<"enter title: ";
cin>>title;
try
{
iuom=uomdao.getByTitle(title);
cout<<"code: "<<iuom->getCode()<<", title: "<<iuom->getTitle()<<endl;
}catch (DAOException daoExc)
{
cout<<daoExc.what()<<endl;
}

}


if(ch==5)
{

cout<<"enter code: ";
cin>>i;
try
{
i=uomdao.codeExist(i);
cout<<"code exist"<<endl;
} catch (DAOException daoExc)
{
cout<<daoExc.what()<<endl;
}

}


if(ch==6)
{
cout<<"enter title: ";
cin>>title;
try
{
i=uomdao.titleExist(title);
cout<<title<<" exist"<<endl;

}catch (DAOException daoExc)
{
cout<<daoExc.what()<<endl;
}

}


if(ch==7)
{
cout<<"enter code : ";
cin>>i;
m.setCode(i);
cout<<"enter title : ";
cin>>title;
m.setTitle(title);
try
{
uomdao.update(&m);
cout<<"updation done"<<endl;
}catch (DAOException daoExc)
{
cout<<daoExc.what()<<endl;
}



}


if(ch==8)
{
cout<<"enter code: ";
cin>>i;
cout<<"enter title: ";
cin>>title;
m.setTitle(title);
m.setCode(i);
try
{
uomdao.remove(&m);
cout<<"removed"<<endl;
}catch (DAOException exc)
{
cout<<exc.what()<<endl;
}


}

if(ch==9) break;





}


cout<<"Number of records: "<<uomdao.getCount()<<endl;
return 0;
}