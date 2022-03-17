#include<uomdao>
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
    return NULL;
}
abc::IUnitOfMeasurement * UnitOfMeasurementDAO::getByTitle(string title) throw(DAOException)
{
    return NULL;
}
forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementDAO::getAll() throw(DAOException)
{
    return NULL;
}
int UnitOfMeasurementDAO::getCount() throw(DAOException)
{
    return 0;
}
int UnitOfMeasurementDAO::codeExist(int code) throw(DAOException)
{
    return 0;
}
int UnitOfMeasurementDAO::titleExist(string title) throw(DAOException)
{
    return 0;
}