#pragma once 

#include "ritual.h"

class Standstill : public Ritual {

public: 
    Standstill();

    void execute(Notification notification) override;

};