#ifndef REPORT_H
#define REPORT_H

#include "args.h"
#include "context.h"

struct Report
{
	static void generate(const Args &args, const ImpactContext &context);
};

#endif
