#include "fin_recipes.h"

void term_structure_class_interpolated::clear(){
    times_.erase(times_.begin(), times_.end());
    yields_.erase(yields_.begin(), yields_.end());
};

term_structure_class_interpolated::term_structure_class_interpolated():term_structure_class(){clear();};

term_structure_class_interpolated::term_structure_class_interpolated(const vector<double>& in_times,
								     const vector<double>& in_yields) {
    clear();
    if (in_times.size()!=in_yields.size()) return;
    times_= vector<double>(in_times.size());
    yields_= vector<double>(in_yields.size());
    for (int i=0;i<in_times.size();i++) {
	times_[i]=in_times[i];
	yields_[i]=in_yields[i];
    };
};

term_structure_class_interpolated::~term_structure_class_interpolated(){ clear();};

term_structure_class_interpolated::term_structure_class_interpolated(const term_structure_class_interpolated& term) {
    times_           = vector<double> (term.no_observations());
    yields_          = vector<double> (term.no_observations());
    for (int i=0;i<term.no_observations();i++){
	times_[i]    = term.times_[i];
	yields_[i]   = term.yields_[i];
    };
};

term_structure_class_interpolated 
term_structure_class_interpolated::operator= (const term_structure_class_interpolated& term) {
    times_           = vector<double> (term.no_observations());
    yields_          = vector<double> (term.no_observations());
    for (int i=0;i<term.no_observations();i++){
	times_[i]    = term.times_[i];
	yields_[i]   = term.yields_[i];
    };
    return (*this);
};

double term_structure_class_interpolated::r(const double& T) const {
    return term_structure_yield_linearly_interpolated(T, times_, yields_); 
};

void 
term_structure_class_interpolated::set_interpolated_observations(vector<double>& in_times,
								 vector<double>& in_yields) {
    clear();
    if (in_times.size()!=in_yields.size()) return;
    times_= vector<double>(in_times.size());
    yields_= vector<double>(in_yields.size());
    for (int i=0;i<in_times.size();i++) {
	times_[i]=in_times[i];
	yields_[i]=in_yields[i];
    };
};
