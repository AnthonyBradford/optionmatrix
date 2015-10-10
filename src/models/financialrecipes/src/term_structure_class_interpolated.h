#ifndef _TERM_STRUCTURE_CLASS_INTERPOLATED_
#define _TERM_STRUCTURE_CLASS_INTERPOLATED_

#include "term_structure_class.h"
#include <vector>
using namespace std;

class term_structure_class_interpolated : public term_structure_class {
private: 
    vector<double> times_;     // use to keep a list of yields
    vector<double> yields_;
    void clear();
public:
    term_structure_class_interpolated();
    term_structure_class_interpolated(const vector<double>& times, const vector<double>& yields);
    virtual ~term_structure_class_interpolated();
    term_structure_class_interpolated(const term_structure_class_interpolated&);
    term_structure_class_interpolated operator= (const term_structure_class_interpolated&);

    int no_observations() const { return times_.size(); };
    virtual double r(const double& T) const;
    void set_interpolated_observations(vector<double>& times, vector<double>& yields);
};

#endif
