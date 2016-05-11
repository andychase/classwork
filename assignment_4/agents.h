//
// Created by Andy Chase on 5/10/16.
//

#ifndef ASSIGNMENT_4_AGENTS_H
#define ASSIGNMENT_4_AGENTS_H

void GrainDeer(GrainState *grainState);
void Grain(GrainState *grainState);
void Watcher(GrainState *grainState);
void Disease(GrainState *grainState);
GrainState CalcTempAndPrecip(struct GrainState *grainState);

#endif //ASSIGNMENT_4_AGENTS_H
