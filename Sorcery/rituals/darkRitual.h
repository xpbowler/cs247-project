#pragma once 

#include "ritual.h"

class DarkRitual : public Ritual {

public: 
    DarkRitual();

    void execute(Notification notification) override;

};

