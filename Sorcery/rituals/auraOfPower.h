#pragma once 

#include "ritual.h"

class AuraOfPower : public Ritual {

public: 

    AuraOfPower();

    void execute(Notification notification) override;

};