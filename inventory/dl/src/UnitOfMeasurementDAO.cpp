#include<uomdao>
using namespace inventory;
using namespace data_layer;
    
void UnitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement) throw(DAOException)
{
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

int main()
{
  abc::IUnitOfMeasurementDAO *unitOFMeasurement;
  unitOFMeasurement=new UnitOfMeasurementDAO;
  
    return 0;
}