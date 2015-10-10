#include "fin_recipes.h"

vector< vector<term_structure_class_ho_lee> > 
term_structure_ho_lee_build_term_structure_tree(term_structure_class* initial,
						const int& no_steps,
						const double& delta,
						const double& pi){
    vector< vector<term_structure_class_ho_lee> > hl_tree;
    for (int t=0;t<5;++t){
	hl_tree.push_back(vector<term_structure_class_ho_lee>());
	for (int j=0;j<=t;++j){
	    term_structure_class_ho_lee hl(initial,t,j,delta,pi);
	    hl_tree[t].push_back(hl);
	};
    };
    return hl_tree;
};
