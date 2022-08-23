#pragma once
#include "ClassFlow.h"

#include "ClassFlowPostProcessing.h"

#include <string>

class ClassFlowFirebase :
    public ClassFlow
{
protected:
    std::string clientname;
    std::string OldValue;
	ClassFlowPostProcessing* flowpostprocessing;
	void SetInitialParameter(void);
public:
    ClassFlowFirebase();
    ClassFlowFirebase(std::vector<ClassFlow*>* lfc);
    ClassFlowFirebase(std::vector<ClassFlow*>* lfc, ClassFlow *_prev);

    bool ReadParameter(FILE* pfile, string& aktparamgraph);
    bool doFlow(string time);
    string name() {return "ClassFlowFirebase";};
};

