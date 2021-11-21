#include "directoryhierarchy.hh"

DirectoryHierarchy::DirectoryHierarchy() {

    wd_ = nullptr;

}

DirectoryHierarchy::~DirectoryHierarchy()
{

}

/* Description: Adds a new directory to the datastructure.
 * Parameters:
 *  Param1: Director's ID (name) string
 *  Param2: Director's timestamp
 *  Param3: Director's size
 *  Param4: Output-stream for error-printing
 * Errormessages:
 *  If director's ID is already in datastructure:
 *      "Error. Directory already added."
 */
void DirectoryHierarchy::addNewDirectory(const std::string &id, const std::string &timestamp, int size, std::ostream &output) {

    Directory* d = new Directory({id, timestamp, size});

    directories_.push_back(d);

}

/* Description: Adds a new directory-parentdirectory relation.
 * Parameters:
 *  Param1: ID of the directory
 *  Param2: ID of the directory's parent
 *  Param3: Output-stream for error-printing
 * Error messages:
 *  If ID wasn't found in datastructure:
 *      "Error. <ID> not found."
 */
void DirectoryHierarchy::addRelation(const std::string &directory, const std::string &parent, std::ostream &output) {

    Directory* d = getPointer(directory);
    if (d->parent_ == nullptr) {
        return;
    }

    Directory* p = getPointer(parent);

    d->parent_ = p;
    p->subdirectories_.push_back(d);

}

void DirectoryHierarchy::commandPrintWorkingDirectory(std::ostream &output) const
{

}

void DirectoryHierarchy::commandList(std::ostream &output) const
{

}

void DirectoryHierarchy::commandDiskUsage(std::ostream &output) const
{

}

void DirectoryHierarchy::commandChangeDirectory(const std::string &id, std::ostream &output)
{

}

void DirectoryHierarchy::commandFind(const std::string &id, const int n, std::ostream &output) const
{

}

void DirectoryHierarchy::commandAsOldAs(const std::string &id, std::ostream &output) const
{

}

void DirectoryHierarchy::commandGreatest(const std::string &id, std::ostream &output) const
{

}

void DirectoryHierarchy::commandSmallest(const std::string &id, std::ostream &output) const
{

}

Directory *DirectoryHierarchy::getPointer(const std::string &id) const {

    for (auto d : directories_) {
        if (d->id_ == id) {
            return d;
        }
    }

}
