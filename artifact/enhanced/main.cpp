#include "InMemoryStudentRepository.h"
#include "StudentService.h"
#include "StudentController.h"

// this is where i build the three layers and connect them together.
// this main is the ONLY place that know we use the memory repository.
// in module five, when i add the database, i only change the first line
// for a database repo and all the rest of the program keep working same :)
int main() {
    InMemoryStudentRepository repository;   // data layer (in memory for now)
    StudentService service(repository);     // logic layer, has the rules
    StudentController controller(service);  // the layer that talk with person

    controller.run();
    return 0;
}
/* emily cruz was here :) */
