#include "directoryhierarchy.hh"
#include <algorithm>

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

    Directory *d = new Directory({id, timestamp, size});

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

    Directory *d = getPointer(directory);
    if (d == nullptr) {
        output << "Error. " << directory << " not found." << std::endl;
    }
    if (parent == EMPTY) {
        return;
    }
    Directory* p = getPointer(parent);

    d->parent_ = p;
    p->subdirectories_.push_back(d);

    sortSubdirectories(p);

}

/* Methods implementing commands */

/* Description: Prints the current working directory with its path.
 * Parameters:
 *  Param1: Output-stream for printing
 * Errormessages:
 *  None.
 */
void DirectoryHierarchy::commandPrintWorkingDirectory(std::ostream &output) const {

    if (wd_ == nullptr) {
        output << "/home";
    } else {
        printPath(wd_, output);
    }

    output << std::endl;

}

/* Description: Prints the subdirectories of the current working directory.
 * Parameters:
 *  Param1: Output-stream for printing
 * Errormessages:
 *  None.
 */
void DirectoryHierarchy::commandList(std::ostream &output) const {

    if (wd_ == nullptr) {
        for (auto d : directories_) {
            if (d->parent_ == nullptr) {
                output << d->id_ << ", " << d->timestamp_ << ", " << d->size_ << std::endl;
            }
        }
    } else {
        for (auto d : wd_->subdirectories_) {
            output << d->id_ << ", " << d->timestamp_ << ", " << d->size_ << std::endl;
        }
    }

}

/* Description: Prints the disk usage of the current working directory.
 * Disk usage is counted as the sum of the sizes of the current working
 * directory and all its subdirectories.
 * Parameters:
 *  Param1: Output-stream for printing
 * Errormessages:
 *  None.
 */
void DirectoryHierarchy::commandDiskUsage(std::ostream &output) const {

    int i = 0;

    int& du = i;

    if (wd_ == nullptr) {
        for (auto d : directories_) {
            if (d->parent_ == nullptr) {
                getSubdirectorySizes(d, du);
                output << du << " /" << d->id_ << std::endl;
                du = 0;
            }
        }
    } else {
        for (auto d : wd_->subdirectories_) {
            getSubdirectorySizes(d, du);
            output << du << " /" << d->id_ << std::endl;
            du = 0;
        }
    }

}

/* Description: Changes the working directory to the subdirectory ID,
 * or home, or to the parent of the current working directory.
 *  Param1: ID of the directory, or "~", or "..".
 *  Param2: Output-stream for printing
 * Errormessages:
 *  If ID is not a subdirectory of the current working directory,
 *  prints the error message:
 *      "Error. <ID> not found."
 *  If the current working directory is home and if ID is "..",
 *  prints the error message:
 *      "Error. Already at the root."
 */
void DirectoryHierarchy::commandChangeDirectory(const std::string &id, std::ostream &output) {

    if (id == "~") {
        wd_ = nullptr;
    } else if (id == "..") {
        if (wd_ == nullptr) {
            output << "Error. Already at the root." << std::endl;
        } else {
            wd_ = wd_->parent_;
        }
    } else {
        if (getPointer(id) != nullptr) {
            wd_ = getPointer(id);
        } else {
            output << "Error. " << id << " not found." << std::endl;
        }
    }

}

/* Description: Finds the subdirectory ID of the current working directory
 * and prints all its subdirectories with their paths down to level n.
 * Parameters:
 *  Param1: ID of the subdirectory
 *  Param2: Maximum distance from the current working directory
 *  (n-1 times "hierarchy").
 *  Param3: Output-stream for printing
 * Errormessages:
 *  If ID is not a subdirectory of the current working directory,
 *  prints the error message:
 *      "Error. <ID> not found."
 *  If Param2's value is less than 1, prints the error message:
 *      "Error. Level can't be less than 1.
 */
void DirectoryHierarchy::commandFind(const std::string &id, const int n, std::ostream &output) const {
    
    if (n < 1) {
        output << "Error. Level can't be less than 1.";
        return;
    }

    if (wd_ == nullptr) {
        for (Directory* d : directories_) {
            if (d->parent_ == nullptr) {
                findRecursive(d, 0, n, wd_->id_, output);
            }
        }
    }

    for (auto d : wd_->subdirectories_) {
        findRecursive(d, 0, n, wd_->id_, output);
    }
    
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

    return nullptr;
    
}

void DirectoryHierarchy::findRecursive(Directory* d, int depth, int max_depth, std::string current_path, std::ostream &output) const {

    current_path += "/" + d->id_;
    output << current_path << std::endl;

    depth++;

    if(depth < max_depth) {
        for (auto d_child : d->subdirectories_) {
            findRecursive(d_child, depth, max_depth, current_path, output);
        }
    }

}

IdSet DirectoryHierarchy::getSubdirectors(const int n, std::string path) const {
    

    
}

void DirectoryHierarchy::printPath(Directory *dir, std::ostream &output) const {

    if (dir->parent_ != nullptr) {
        printPath(dir->parent_, output);
        output << "/" + dir->id_;
    } else {
        output << "/home/" + dir->id_;
    }

}

void DirectoryHierarchy::getSubdirectorySizes(Directory *dir, int &du) const {

    //td::cout << "directory: " << dir->id_ << ", size: " << dir->size_ << ", du: " << du << std::endl;

    if (dir->subdirectories_.empty()) {
        //std::cout << "finished, adding: " << dir->size_ << " to du." << std::endl << std::endl;
        du += dir->size_;
    } else {
        for (Directory *d : dir->subdirectories_) {
            getSubdirectorySizes(d, du);
        }
        //std::cout << "adding top directory: " << dir->size_ << " to du." << std::endl << std::endl;
        du += dir->size_;
    }

}

void DirectoryHierarchy::sortSubdirectories(Directory *dir) {

    std::cout << "weve made it this far, sorting " + dir->id_ << std::endl;

    std::sort(dir->subdirectories_.begin(), dir->subdirectories_.end(), Directory());

}

bool DirectoryHierarchy::compareDirectories(Directory* a, Directory* b) {

    return a->id_ < b->id_;

}
