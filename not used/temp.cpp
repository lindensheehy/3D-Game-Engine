
template<typename type>
class LinkedList;

class WindowHandle;

class DataClass;

class BindManager {

    public:

        struct Bind {
            WindowHandle* handle;
            void (*func)(void*);
        };  

        LinkedList<Bind>* BindSet;

        BindManager() {

            this->binding = new Binding();

        }

        class Binding {

            public:

                Binding() {

                    this->window3 = new Window3();

                    // Add more instantiations as needed

                }
            
                void bindWindow1(WindowHandle* handle);

                void bindWindow2(WindowHandle* handle);

                class Window3 {

                    public:

                        DataClass* someData;

                        Window3() : someData(nullptr) {} 

                        void bindWindow3(WindowHandle* handle);

                    private:

                        // Functions bound to buttons
                        void window3Button1();
                        void window3Button2();

                };
                Window3* window3;

                // Add more classes as needed

        };


        Binding* binding;
    
};



int* p;

void func() {
    int scoped = 1;
    p = &scoped;
    return;
}

int main() {
    p = nullptr;
    func();
    return (*p);
}
 


#pragma once
#include "util/Utility.h"
#include "util/LinkedList.h"
#include "xml/Core.h"
namespace Xml{struct Parameter{const char* name;ParameterType type;};class ParameterInfo{friend class ParameterInfoBuilder;public:~ParameterInfo();ParameterType matchParameter(const char* name,
int* positionOut);private:ParameterInfo(LinkedList<Parameter*>* params);char* names;int* namesIndexes;int* namesLengths;ParameterType* types;int length;};class ParameterInfoBuilder{friend class 
ParameterInfo;public:ParameterInfoBuilder();~ParameterInfoBuilder();ParameterInfo* build();void reset();void addParameter(const char* name,ParameterType type,int position);void addParameter(
char* name,ParameterType type,int position);private:LinkedList<Parameter*>* params;};}



#include <windows.h>
#include <cstring>
#include "util/Utility.h"
#include "util/Log.h"
#include "util/FileReader.h"

class FileNavigator {

public:

    HANDLE hCurrentFile = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATAA fileData{};
    char* workingPath = nullptr;
    bool doRecursion = false;
    bool considerDirs = false;

    FileNavigator(const char* path) {
        setWorkingPath(path);
    }

    ~FileNavigator() {
        if (hCurrentFile != INVALID_HANDLE_VALUE) {
            FindClose(hCurrentFile);
        }
        delete[] workingPath;
    }

    void setWorkingPath(const char* newPath) {
        if (workingPath) {
            delete[] workingPath;
        }

        size_t len = strlen(newPath);
        workingPath = new char[len + 2]; // +1 for null, +1 for optional backslash
        strcpy(workingPath, newPath);

        // Ensure the path ends with a slash
        if (len > 0 && workingPath[len - 1] != '\\') {
            workingPath[len] = '\\';
            workingPath[len + 1] = '\0';
            workingPathEndIndex = static_cast<int>(len + 1);
        } else {
            workingPathEndIndex = static_cast<int>(len);
        }

        // Validate path
        DWORD attrs = GetFileAttributesA(workingPath);
        if (attrs == INVALID_FILE_ATTRIBUTES || !(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
            logWrite("FileNavigator Error: Invalid working path: %s", workingPath);
        }
    }

    void iterStart(const char* searchPath) {
        if (hCurrentFile != INVALID_HANDLE_VALUE) {
            FindClose(hCurrentFile);
            hCurrentFile = INVALID_HANDLE_VALUE;
        }

        char fullSearch[MAX_PATH];
        strcpy(fullSearch, workingPath);
        strcat(fullSearch, searchPath);

        hCurrentFile = FindFirstFileA(fullSearch, &fileData);
        if (hCurrentFile == INVALID_HANDLE_VALUE) {
            logWrite("FileNavigator Warning: No matches found for pattern: %s", fullSearch);
        }
    }

    void iterNext() {
        if (hCurrentFile != INVALID_HANDLE_VALUE) {
            if (!FindNextFileA(hCurrentFile, &fileData)) {
                FindClose(hCurrentFile);
                hCurrentFile = INVALID_HANDLE_VALUE;
            }
        }
    }

    bool iterHasNext() {
        while (hCurrentFile != INVALID_HANDLE_VALUE) {
            bool isDir = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
            if (isDir) {
                if (!considerDirs || strcmp(fileData.cFileName, ".") == 0 || strcmp(fileData.cFileName, "..") == 0) {
                    iterNext();
                    continue;
                }
            }
            return true;
        }
        return false;
    }

    char* readCurrentFile() {
        if (!iterHasNext()) {
            return nullptr;
        }

        char filePath[MAX_PATH];
        strcpy(filePath, workingPath);
        strcat(filePath, fileData.cFileName);

        return readFile(filePath); // Provided utility
    }

private:
    int workingPathEndIndex = 0;

};



#include <vector>

class Vec2 {
public:
    float x = 0.0f;
    float y = 0.0f;
    Vec2();
    Vec2& set(Vec2& other);
    Vec2& add(Vec2& other);
    Vec2& normalize();
    Vec2& rotate(float degrees);
};

constexpr int FOV = 90;

class Entity;
Entity* checkForCollision(Vec2& ray);

int getRange(int angle);

void func() {

    std::vector<Entity*> drawList;

    Vec2 playerFacing;
    Vec2 rayCastStart;
    rayCastStart.set(playerFacing).normalize();
    rayCastStart.rotate(-45);

    Vec2 rayCastIteration;
    for (int i = 0; i < FOV; i++) {

        rayCastIteration.set(rayCastStart);

        int range = getRange(i);
        for (int j = 0; j < range; j++) {

            Entity* foundCollision = checkForCollision(rayCastIteration);

            if (foundCollision != nullptr) {
                drawList.push_back(foundCollision);
                continue;
            }

            rayCastIteration.add(rayCastStart);

        }

        rayCastStart.rotate(1);

    }    
    
}

class Entity {};
class Projectile : public Entity {
public:
    float x, y;
    Projectile(float x, float y) : x(x), y(y) {}
    void draw();
};

bool checkProjectile(Projectile* p) {

    Projectile p(1, 2);

    std::vector<Projectile*> list;

    void* mem = operator new(sizeof(Projectile) * 10);
    Projectile* p2 = new (mem) Projectile(1, 2);
    Projectile* p2 = new (mem + sizeof(Projectile)) Projectile(1, 2);

}

class Player {

    public:

        Player();

        int timer = 0;
        std::vector<Projectile*> projectileList;

        void shoot() {

            if (this->timer != 0) return;

            Projectile* p = new Projectile();

            this->projectileList.push_back(p);
            this->timer = 120;

        }

        void nextFrame() {
            if (this->timer > 0) this->timer--;
            return;
        }

        void draw() {

            for (Projectile* p : this->projectileList) {
                p->draw();
            }

        }

        void checkProjectiles() {

            for (Projectile* p : this->projectileList) {

                bool shouldDelete = checkProjectile(p);

                if (shouldDelete) {

                    this->projectileList.erase(p);

                    delete p;

                }

            }

        }

};
