#ifndef _TERM_STRUCTURE_CLASS_H_
#define _TERM_STRUCTURE_CLASS_H_

class term_structure_class {
public:
    virtual double r(const double& t) const; // yield on zero coupon bond
    virtual double d(const double& t) const; // discount factor/price of zero coupon bond
    virtual double f(const double& t1, const double& t2) const; // forward rate
    virtual ~term_structure_class();
};

#endif
