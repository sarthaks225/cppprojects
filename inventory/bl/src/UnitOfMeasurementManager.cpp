#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<bl/blexception>
#include<stringutils>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/iuom>
#include<bl/uom>

#include<iostream>
#include<map>
#include<utility>
#include<forward_list>
using namespace std;

using namespace std;
using namespace inventory;
using namespace business_layer;
int UnitOfMeasurementTitleComparetor::operator()(string *left,string *right)
{
    return compareStringIgnoreCase((*left).c_str(),(*right).c_str())<0;
}
UnitOfMeasurementManager::DataModel UnitOfMeasurementManager::dataModel;
UnitOfMeasurementManager::DataModel:: DataModel()
{
this->populateDataStructure();
}
UnitOfMeasurementManager::DataModel::~DataModel()
{

}
void UnitOfMeasurementManager::DataModel:: populateDataStructure()
{
 forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurements;
 inventory::data_layer::UnitOfMeasurementDAO uomdao;
 try
 {
 dlUnitOfMeasurements=uomdao.getAll();
 _UnitOfMeasurement *_unitOfMeasurement;
 inventory::data_layer::abc:: IUnitOfMeasurement *dliuom;
 forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i=dlUnitOfMeasurements->begin();
 string *title;
 while(i!=dlUnitOfMeasurements->end())
 {
     dliuom=*i;
     title=new string(dliuom->getTitle());
    _unitOfMeasurement=new _UnitOfMeasurement;
    _unitOfMeasurement->code=dliuom->getCode();
    _unitOfMeasurement->title=title;
    UnitOfMeasurementManager::dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(dliuom->getCode(),_unitOfMeasurement));
    UnitOfMeasurementManager::dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(title,_unitOfMeasurement));
    delete dliuom;
    ++i;
 }
dlUnitOfMeasurements->clear();
delete dlUnitOfMeasurements;
 }
 catch(inventory::data_layer::DAOException &daexc)
 {
 // do nothing
 }

}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}
 void UnitOfMeasurementManager:: addUnitOfMeasurement(abc::IUnitOfMeasurement*unitOfMeasurement) throw(BLException)
 {
     BLException blexception;
    if(unitOfMeasurement==NULL)
    {
        blexception.setGenericException("unit of measurement is required,NULL ecountered");
        throw blexception;
    }
    int code=unitOfMeasurement->getCode();
    string title=unitOfMeasurement->getTitle();
    string vTitle=stringTrimme(title);
    if(code!=0)
    {
        blexception.addPropertyException("code","code should be zero");
    }
    if(vTitle.length()==0)
    {
        blexception.addPropertyException("title","title length should not zero");
    }
    if(title.length()>50)
    {
        blexception.addPropertyException("title","title lenght should not be more then 50 characters");
    }
    if(blexception.hasExceptions())
    {
        throw blexception;
    }

    map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparetor>::iterator i;
    i=dataModel.titleWiseMap.find(&title);
    if(i!=dataModel.titleWiseMap.end())
    {
        blexception.addPropertyException("title","title already  exists");
        throw blexception;
    }
    inventory::data_layer::UnitOfMeasurementDAO dluomdao;
    inventory::data_layer::UnitOfMeasurement *dluom;
    dluom=new inventory::data_layer::UnitOfMeasurement;
    dluom->setCode(0);
    dluom->setTitle(vTitle);
    try
    {
        dluomdao.add(dluom);
        unitOfMeasurement->setCode(dluom->getCode());
        _UnitOfMeasurement *_unitOfMeasurement;
        _unitOfMeasurement=new _UnitOfMeasurement;
        _unitOfMeasurement->code=dluom->getCode();
        string *t;
        t=new string(vTitle);
        _unitOfMeasurement->title=new string(*t);
        dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(dluom->getCode(),_unitOfMeasurement));
        dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,_unitOfMeasurement));
    }
    catch (inventory::data_layer:: DAOException dlexc)
    {
        blexception.setGenericException(dlexc.what());
        throw blexception;
    }
    
 }
 void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
 {
     if(unitOfMeasurement==NULL)
    {
        throw BLException("nothing to update");

    }
    int code=unitOfMeasurement->getCode();
    string title=unitOfMeasurement->getTitle();
    string vTitle=stringTrimme(title);
    BLException blexc;
    if(code<=0)
    {
        blexc.addPropertyException("code","code must be greater then zero");
    }
    if(vTitle.length()==0)
    {
        blexc.addPropertyException("title","Title is empty");
    }
    if(vTitle.length()>50)
    {
        blexc.addPropertyException("title","Title length should not exceed 50");
    }
    if(blexc.hasExceptions())
    {

        throw blexc;
    }

    map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparetor>::iterator i;
    i=dataModel.titleWiseMap.find(&vTitle);
    if(i!=dataModel.titleWiseMap.end())
    {
        blexc.addPropertyException("title","title already exists, updation failed");;
        throw blexc;
    }
    map<int,_UnitOfMeasurement *>::iterator j;
    j=dataModel.codeWiseMap.find(code);
    if(j==dataModel.codeWiseMap.end())
    {
        blexc.addPropertyException("code","code does not match, updation failed");
        throw blexc;
    }

    inventory::data_layer::UnitOfMeasurementDAO dluomdao;
    inventory::data_layer::UnitOfMeasurement *dluom;
    dluom=new inventory::data_layer::UnitOfMeasurement;
    dluom->setCode(code);
    dluom->setTitle(vTitle);

    try
    {
        _UnitOfMeasurement *_unitOfMeasurement;
        _unitOfMeasurement=new _UnitOfMeasurement;
        _unitOfMeasurement->code=code;
        string *t;
        t=new string(vTitle);
        j=dataModel.codeWiseMap.find(code);
        vTitle=*(j->second->title);
        dataModel.codeWiseMap.erase(j->first);
        i=dataModel.titleWiseMap.find(&vTitle);
        dataModel.titleWiseMap.erase(i->first);
        _unitOfMeasurement->code=code;
        _unitOfMeasurement->title=new string(*t);
        dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurement *>(dluom->getCode(),_unitOfMeasurement));
        dataModel.titleWiseMap.insert(pair<string *,_UnitOfMeasurement *>(t,_unitOfMeasurement));
        dluomdao.update(dluom);
    }
    catch (inventory::data_layer:: DAOException dlexc)
    {
        blexc.setGenericException(dlexc.what());
        throw blexc;
    }




 }
 void UnitOfMeasurementManager::removeUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
 {

    if(unitOfMeasurement==NULL)
    {
        throw BLException("nothing to update");
    }
    int code=unitOfMeasurement->getCode();
    string title=unitOfMeasurement->getTitle();
    string vTitle=stringTrimme(title);
    BLException blexc;
    if(code<=0)
    {
        blexc.addPropertyException("code","code must be greater then zero");
    }
    if(vTitle.length()==0)
    {
        blexc.addPropertyException("title","Title is empty");
    }
    if(vTitle.length()>50)
    {
        blexc.addPropertyException("title","Title length should not exceed 50");
    }
    if(blexc.hasExceptions())
    {

        throw blexc;
    }

    char exc[150];
    sprintf(exc,"Code : %d with title : (%s) not exists",code,title.c_str());
    map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparetor>::iterator i;
    i=dataModel.titleWiseMap.find(&vTitle);
    if(i==dataModel.titleWiseMap.end())
    {
        throw BLException(exc);
    }

    map<int,_UnitOfMeasurement *>::iterator j;
    j=dataModel.codeWiseMap.find(code);
    if(j==dataModel.codeWiseMap.end() || code!=(*i).second->code)
    {
        throw BLException(exc);
    }

    inventory::data_layer::UnitOfMeasurementDAO dluomdao;
    inventory::data_layer::UnitOfMeasurement dluom;
    dluom.setCode(code);
    dluom.setTitle(vTitle);

    try
    {
        dluomdao.remove(&dluom);
        j=dataModel.codeWiseMap.find(code);
        dataModel.codeWiseMap.erase(j->first);
        i=dataModel.titleWiseMap.find(&vTitle);
        dataModel.titleWiseMap.erase(i->first);
        
    }
    catch (inventory::data_layer:: DAOException dlexc)
    {
        blexc.setGenericException(dlexc.what());
        throw blexc;
    }



 }
 void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
 {

    if(title.length()==0)
    {
        throw BLException("nothing to update");
    }
    string vTitle=stringTrimme(title);
    BLException blexc;
    if(vTitle.length()==0)
    {
        blexc.addPropertyException("title","Title is empty");
    }
    if(vTitle.length()>50)
    {
        blexc.addPropertyException("title","Title length should not exceed 50");
    }
    if(blexc.hasExceptions())
    {
      throw blexc;
    }

    char exc[150];
    sprintf(exc,"title : (%s) not exists",title);
    map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparetor>::iterator i;
    i=dataModel.titleWiseMap.find(&vTitle);
    if(i==dataModel.titleWiseMap.end())
    {
        throw BLException(exc);
    }

    map<int,_UnitOfMeasurement *>::iterator j;
    int code;
    inventory::data_layer::UnitOfMeasurementDAO dluomdao;
    inventory::data_layer::UnitOfMeasurement dluom;
    i=dataModel.titleWiseMap.find(&vTitle);
    code=(*i).second->code;
    j=dataModel.codeWiseMap.find(code);
    dluom.setTitle(vTitle);
    dluom.setCode(code);
    
    try
    {
        dluomdao.remove(&dluom);
        dataModel.codeWiseMap.erase(j->first);
        dataModel.titleWiseMap.erase(&vTitle);     
    }
    catch (inventory::data_layer:: DAOException dlexc)
    {
        blexc.setGenericException(dlexc.what());
        throw blexc;
    }


 }
 void UnitOfMeasurementManager::removeUnitOFMeasurementByCode(int code) throw(BLException)
 {

     if(code<=0)
    {
        throw BLException("invlid code, code must be greater ther 0");
    }
    BLException blexc;
    
    map<int,_UnitOfMeasurement *>::iterator j;
    j=dataModel.codeWiseMap.find(code);
    if(j==dataModel.codeWiseMap.end())
    {
        throw BLException("code not exists");
    }

    string title;
    title=*((*j).second->title);
    map<string *,_UnitOfMeasurement *,UnitOfMeasurementTitleComparetor>::iterator i;
    i=dataModel.titleWiseMap.find(&title);
    inventory::data_layer::UnitOfMeasurementDAO dluomdao;
    inventory::data_layer::UnitOfMeasurement dluom;
    dluom.setTitle(title);
    dluom.setCode(code);
    
    try
    {
        dluomdao.remove(&dluom);
        dataModel.codeWiseMap.erase(code);
        dataModel.titleWiseMap.erase(&title);     
    }
    catch (inventory::data_layer:: DAOException dlexc)
    {
        blexc.setGenericException(dlexc.what());
        throw blexc;
    }


 }
 
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int code) throw(BLException)
{

    if(code<=0)
    {
        throw BLException("invlid code, code must be greater ther 0");
    }
    BLException blexc;
    map<int,_UnitOfMeasurement *>::iterator j;
    j=dataModel.codeWiseMap.find(code);
    if(j==dataModel.codeWiseMap.end())
    {
        throw BLException(string(to_string(code))+string("code not exists"));
    }

    string title;
    title=*((*j).second->title);
    inventory::data_layer::UnitOfMeasurement *dluom;
    dluom=new inventory::data_layer::UnitOfMeasurement;
    dluom->setTitle(title);
    dluom->setCode(code);
    
    return (abc::IUnitOfMeasurement *) dluom;

}
abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string &title) throw(BLException)
{
    title=stringTrimme(title);
    if(title.length()==0)
    {
        throw BLException("invlid title, title lenth must be greater then 0");
    }
    BLException blexc;
    map<string *,_UnitOfMeasurement *>::iterator j;
    j=dataModel.titleWiseMap.find(&title);
    if(j==dataModel.titleWiseMap.end())
    {
        throw BLException("given title in not exists");
    }
    int code;
    code=(*j).second->code;
    title=*(j->second->title);
    inventory::data_layer::UnitOfMeasurement *dluom;
    dluom=new inventory::data_layer::UnitOfMeasurement;
    dluom->setTitle(title);
    dluom->setCode(code);
    
    return (abc::IUnitOfMeasurement *) dluom;

}

 forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getAllUnitOfMeasurement() throw(BLException)
 {
     
    map<int,_UnitOfMeasurement *>::iterator i;
    i=dataModel.codeWiseMap.begin();
    if(dataModel.codeWiseMap.end()==i)
    {
        throw BLException("not single unit of measurement added,Please add unit of measurement");
    }
    forward_list<abc::IUnitOfMeasurement *> *list;
    list=new forward_list<abc::IUnitOfMeasurement *>;
    forward_list<abc::IUnitOfMeasurement *>::iterator j;
    j=list->before_begin();
    UnitOfMeasurement *uom;
    _UnitOfMeasurement *_uom;
    while(i!=dataModel.codeWiseMap.end())
    {
        _uom=(*i).second;
        uom=new UnitOfMeasurement;
        uom->setCode(_uom->code);
        uom->setTitle(*(_uom->title));
        j=list->insert_after(j,uom);
        ++i;
    }


    return list;
 }
 int UnitOfMeasurementManager::unitOfMeasurementCodeExists(int code) throw(BLException)
 {

    if(code<=0)
    {
        return 0;
    }
    BLException blexc;
    map<int,_UnitOfMeasurement *>::iterator j;
    j=dataModel.codeWiseMap.find(code);
    if(j==dataModel.codeWiseMap.end())
    {
       return 0;
    }
    return 1;

 }
 int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string &title) throw(BLException)
 {
    title=stringTrimme(title);
    if(title.length()==0)
    {
        return 0;
    }
    BLException blexc;
    map<string *,_UnitOfMeasurement *>::iterator j;
    j=dataModel.titleWiseMap.find(&title);
    if(j==dataModel.titleWiseMap.end())
    {
        return 0;
    }
    return 1;

 }
 int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
 {
     return dataModel.codeWiseMap.size();

 }


