#include<stdio.h>
#include<uomdao>
#include<uom>
#include<fstream>
#include<string.h>
#include<stringutils>
using namespace inventory;
using namespace data_layer;
    
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
    if(unitOfMeasurement==NULL) throw DAOException("unitOfMeasurement is NULL");
    const string vTitle=unitOfMeasurement->getTitle();
    string title=stringTrimme(vTitle);
    if(title.length()==0)
    {
        throw DAOException("title length is zero");
    }
    if(title.length()>50)
    {
        throw DAOException("title length exceeds 50");
    }
    Head head;
    _UnitOfMeasurement _unitOfMeasurement;
    fstream f(FILE_NAME,ios::in | ios::out | ios::binary);
    if(f.fail())
    {
        f.close();
        ofstream g(FILE_NAME,ios::app | ios::binary);
        head.lastGeneratedCode=1;
        head.numberOfRecords=1;
        g.write((char *)&head,sizeof(Head));
        _unitOfMeasurement.code=1;
        strcpy(_unitOfMeasurement.title,title.c_str());
        g.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
        g.close();
        unitOfMeasurement->setCode(1);
        return;
    }
    f.seekg(0,ios::beg);
    f.read((char *)&head,sizeof(Head));
    if(f.fail())
    {
        f.clear();
        f.seekg(0,ios::beg);
        f.seekp(0,ios::beg);
        head.lastGeneratedCode=1;
        head.numberOfRecords=1;
        f.write((char *)&head,sizeof(Head));
        _unitOfMeasurement.code=1;
        strcpy(_unitOfMeasurement.title,title.c_str());
        f.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
        f.close();
        unitOfMeasurement->setCode(1);
        return;
    }
    while(1)
    {
        
        f.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
        if(f.fail()) break;
        if(compareStringIgnoreCase(title.c_str(),_unitOfMeasurement.title)==0)
        {
            f.close();
            throw DAOException(title+string(" exist"));
        }
    }
    f.clear();
    f.seekp(0,ios::beg);
    f.seekg(0,ios::beg);
    head.lastGeneratedCode++;
    head.numberOfRecords++;
    f.write((char *)&head,sizeof(Head));
   
    f.seekp(0,ios::end);
    _unitOfMeasurement.code=head.lastGeneratedCode;
    strcpy(_unitOfMeasurement.title,title.c_str());
    f.write((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
    f.close();
    unitOfMeasurement->setCode(head.lastGeneratedCode);
}
void UnitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
void UnitOfMeasurementDAO::remove(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByCode(int code) throw(DAOException)
{
    if(code<=0) throw DAOException("Invalid code (code must greater then 0)");
    fstream f(FILE_NAME,ios::in | ios::binary);
    char exception[100];
    sprintf(exception,"Code does not exist %d",code);
    if(f.fail())
    {
        f.close();
        throw DAOException(exception);
    }
    Head head;
    f.read((char *)&head,sizeof(Head));
    if(f.fail())
    {
        f.close();
        throw DAOException(exception);
    }
    _UnitOfMeasurement _unitOfMeasurement;
    while(1)
    {
    f.read((char *) &_unitOfMeasurement,sizeof(_UnitOfMeasurement));
    if(f.fail()) break;
    if(_unitOfMeasurement.code==code)
    {
        UnitOfMeasurement unitOfMeasurement;
        unitOfMeasurement.setCode(_unitOfMeasurement.code);
        unitOfMeasurement.setTitle(_unitOfMeasurement.title);
        abc::IUnitOfMeasurement *iUnitOfMeasurement;
        iUnitOfMeasurement=&unitOfMeasurement;
        f.close();
        return iUnitOfMeasurement;
    }
    }
    f.close();
    throw DAOException(exception);
    return NULL;
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) throw(DAOException)
{
    string vTitle;
    vTitle=stringTrimme(title);
    char i[100];
    if(vTitle.length()==0) throw DAOException("Given title is empty");
    if(vTitle.length()>50) throw DAOException("title length exceeds(more then 50 invalid)");
    ifstream f(FILE_NAME,ios::in | ios::binary);
    if(f.fail()) 
    {
        f.close();
        throw DAOException("No single unit of measurement added");
    }
    Head head;
    f.read((char *)&head,sizeof(Head));
    if(f.fail())
    {
        f.close();
        throw DAOException("NO single unit of measurement added");
    }
    if(head.numberOfRecords==0)
    {
        f.close();
        throw DAOException("NO single unit of measurement added");
    }
    _UnitOfMeasurement  _unitOfMeasurement;
    strcpy(i,vTitle.c_str());
    int j;

    while(1)
    {
        f.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
        if(f.fail()) break;
        j=compareStringIgnoreCase(i,_unitOfMeasurement.title);
        if(j==0)
        {
            f.close();
            UnitOfMeasurement uom;
            uom.setCode(_unitOfMeasurement.code);
            uom.setTitle(_unitOfMeasurement.title);
            abc::IUnitOfMeasurement *iuom;
            iuom=&uom;
            return iuom;
        }
    }

    f.close();
    sprintf(i,"Unit of measurement with title (%s) not found in file",title.c_str());
    throw DAOException(i);
    return NULL;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
    fstream f(FILE_NAME,ios::in | ios::binary);
    if(f.fail())
    {
     f.close();
     throw DAOException("File is not created for unit of measurement or not single entry added");
    }
    Head head;
    f.read((char *) &head,sizeof(Head));
    if(f.fail())
    {
        f.close();
        throw DAOException("File is empty");
    }
    if(head.numberOfRecords==0)
    {
        f.close();
        throw DAOException("Not single unit of measurement added");
    }
    forward_list<abc::IUnitOfMeasurement *> *list;
    list=new forward_list<abc::IUnitOfMeasurement *>;
    abc::IUnitOfMeasurement *iuom;
    _UnitOfMeasurement _uom;
     UnitOfMeasurement *uom;
    forward_list<abc::IUnitOfMeasurement *>::iterator i;
    i=list->before_begin();
   
    while(1)
    {
        uom=new UnitOfMeasurement;
        f.read((char *) &_uom,sizeof(_UnitOfMeasurement));
        if(f.fail()) break;
        uom->setCode(_uom.code);
        uom->setTitle(_uom.title);
        iuom=uom;
        i=list->insert_after(i,iuom);
    }
    f.close();
    return list;
}
int UnitOfMeasurementDAO::getCount() throw(DAOException)
{
    Head head;
    ifstream f(FILE_NAME,ios::in | ios::binary);
    if(f.fail())
    {
    f.close();
     return 0;
    }
    f.read((char *)&head,sizeof(head));
    if(f.fail()) 
    {
    f.close();        
    return 0;
    }
    f.close();
    return head.numberOfRecords;
}
int UnitOfMeasurementDAO::codeExist(int code) throw(DAOException)
{
    if(code<=0) throw DAOException("code must be greater then 0");
    ifstream f(FILE_NAME,ios::in | ios::binary);
    if(f.fail())
    {
     f.close();
     throw DAOException("Not single unit of measurement exists");
    }
    Head head;
    f.read((char *)&head,sizeof(Head));
    if(f.fail()) 
    {
     f.close();
     throw DAOException("Not single unit of measurement exists");
    }
    char i[50];
    sprintf(i,"code :(%d) not exist in file",code);
    if(head.numberOfRecords<code)
    {
     f.close();
     throw DAOException(i);
    }
    _UnitOfMeasurement _uom;
    while(1)
    {
        f.read((char *)&_uom,sizeof(_UnitOfMeasurement));
        if(f.fail()) break;
        if(_uom.code==code)
        {
            f.close();
            return 1;
        }
    }
    f.close();
    throw DAOException(i);
    return 0;
}
int UnitOfMeasurementDAO::titleExist(string title) throw(DAOException)
{

    string vTitle;
    vTitle=stringTrimme(title);
    char i[100];
    if(vTitle.length()==0) throw DAOException("Given title is empty");
    if(vTitle.length()>50) throw DAOException("title length exceeds(more then 50 invalid)");
    ifstream f(FILE_NAME,ios::in | ios::binary);
    if(f.fail()) 
    {
        f.close();
        throw DAOException("No single unit of measurement added");
    }
    Head head;
    f.read((char *)&head,sizeof(Head));
    if(f.fail())
    {
        f.close();
        throw DAOException("NO single unit of measurement added");
    }
    if(head.numberOfRecords==0)
    {
        f.close();
        throw DAOException("NO single unit of measurement added");
    }
    _UnitOfMeasurement  _unitOfMeasurement;
    strcpy(i,vTitle.c_str());
    int j;

    while(1)
    {
        f.read((char *)&_unitOfMeasurement,sizeof(_UnitOfMeasurement));
        if(f.fail()) break;
        j=compareStringIgnoreCase(i,_unitOfMeasurement.title);
        if(j==0)
        {
            f.close();
            return 1;
        }
    }

    f.close();
    sprintf(i,"Unit of measurement with title (%s) not found in file",title.c_str());
    throw DAOException(i);

    return 0;
}