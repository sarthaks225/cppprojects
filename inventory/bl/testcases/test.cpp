#include<iostream>
#include<bl/uommanager>
#include<dl/uomdao>
#include<stringutils>

using namespace inventory;
using namespace business_layer;
int main()
{
string title;
int ch,code;
UnitOfMeasurement uom;
forward_list<abc::IUnitOfMeasurement *> *list;
abc::IUnitOfMeasurement *iuom;
UnitOfMeasurementManager uommanager;
while(1)
{
cout<<endl;
cout<<"1. add uom "<<endl;
cout<<"2. get all "<<endl;
cout<<"3. update uom by using code"<<endl;
cout<<"4. remove uom by using code and title"<<endl;
cout<<"5. remove uom by title"<<endl;
cout<<"6. remove uom by code"<<endl;
cout<<"7. get by code "<<endl;
cout<<"8. get by title"<<endl;
cout<<"9. unitOfMeasurement Code Exists"<<endl;
cout<<"10 unitOfMeasurement Title Exists"<<endl;
cout<<"11 get uom Count"<<endl;
cout<<"12. exit"<<endl;
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
cin>>code;
cout<<"enter new title : ";
cin>>title;
uom.setCode(code);
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

if(ch==4)
{
cout<<"enter code : ";
cin>>code;
cout<<"enter title : ";
cin>>title;
try
{
uom.setCode(code);
uom.setTitle(title);
uommanager.removeUnitOfMeasurement(&uom);
cout<<"removed..."<<endl;
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

if(ch==5)
{
cout<<"enter title to remove uom : ";
cin>>title;
try
{
uommanager.removeUnitOfMeasurementByTitle(title);
cout<<"removed ..."<<endl;
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

if(ch==6)
{
cout<<"enter code to remove uom:";
cin>>code;
try
{
uommanager.removeUnitOFMeasurementByCode(code);
cout<<"removed"<<endl;
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

if(ch==7)
{
cout<<"enter code : ";
cin>>code;
try
{
uom=*(uommanager.getUnitOfMeasurementByCode(code));
cout<<"code: "<<uom.getCode()<<", title: ("<<uom.getTitle()<<")"<<endl;
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
if(ch==8)
{
// get by title
cout<<"enter title : ";
cin>>title;
try
{
uom=*(uommanager.getUnitOfMeasurementByTitle(title));
cout<<"code: "<<uom.getCode()<<", title: ("<<uom.getTitle()<<")"<<endl;
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
if(ch==9)
{
//unitOfMeasurement Code Exists
cout<<"enter code : ";
cin>>code;
if(uommanager.unitOfMeasurementCodeExists(code))
{
cout<<"code : "<<code<<" exists"<<endl;
}
else cout<<"code:"<<code<<"not exists"<<endl;
}

if(ch==10)
{
//unitOfMeasurement Title Exists
cout<<"enter title: ";
cin>>title;
if(uommanager.unitOfMeasurementTitleExists(title))
{
cout<<"title : "<<title<<" exists"<<endl;
}
else cout<<"title : "<<title<<" not exists"<<endl;
}

if(ch==11)
{
cout<<"number uom added : "<<uommanager.getUnitOfMeasurementCount()<<endl;
}

if(ch==12) break;

}


cout<<"end of test"<<endl;
return 0;
}