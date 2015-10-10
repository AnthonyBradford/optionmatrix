class term_structure_class_svensson:public term_structure_class {
private: 
    double beta0_, beta1_, beta2_, beta3_, tau1_, tau2_;
public:
    term_structure_class_svensson(const double& beta0, 
				  const double& beta1,
				  const double& beta2, 
				  const double& beta3, 
				  const double& tau1,
				  const double& tau2);
    virtual double yield(const double& T) const;
};
