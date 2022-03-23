#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<bl/blexception>
#include<bl/uommanager>
#include<bl/iuom>
#include<bl/iuommanager>
#include<bl/uom>
#include<stringutils>

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
 forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurement;
 inventory::data_layer::UnitOfMeasurementDAO uomdao;
 dlUnitOfMeasurement=uomdao.getAll();
}
UnitOfMeasurementManager::UnitOfMeasurementManager()
{
}
 void UnitOfMeasurementManager:: addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
 {}
 void UnitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement) throw(BLException)
 {}
 void UnitOfMeasurementManager::removeUnitOfMeasurement(abc::IUnitOfMeasurement *) throw(BLException)
 {}
 void UnitOfMeasurementManager::removeUnitOfMeasurementByTitle(string &title) throw(BLException)
 {}
 void UnitOfMeasurementManager::removeUnitOFMeasurementByCode(int &code) throw(BLException)
 {}
 abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByCode(int &code) throw(BLException)
 {}
 abc::IUnitOfMeasurement * UnitOfMeasurementManager::getUnitOfMeasurementByTitle(string *title) throw(BLException)
 {}
 forward_list<abc::IUnitOfMeasurement *> * UnitOfMeasurementManager::getAllUnitOfMeasurement() throw(BLException)
 {}
 int UnitOfMeasurementManager::unitOfMeasuremetnCodeExists(int &code) throw(BLException)
 {}
 int UnitOfMeasurementManager::unitOfMeasurementTitleExists(string title) throw(BLException)
 {}
 int UnitOfMeasurementManager::getUnitOfMeasurementCount() throw(BLException)
 {}


