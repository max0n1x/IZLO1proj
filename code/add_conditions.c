#include <stddef.h>
#include "cnf.h"

//
// LOGIN: xpodho08
//

// Tato funkce je prikladem pouziti funkci create_new_clause, add_literal_to_clause a add_clause_to_formula
// Vysvetleni, co dela, naleznete v zadani
void example_condition(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
            // vytvori novou klauzuli
            Clause *example_clause = create_new_clause(num_of_subjects, num_of_semesters);
            // vlozi do klauzule literal x_{i,j}
            add_literal_to_clause(example_clause, true, subject_i, semester_j);
            // vlozi do klauzule literal ~x_{i,j}
            add_literal_to_clause(example_clause, false, subject_i, semester_j);
            // prida klauzuli do formule
            add_clause_to_formula(example_clause, formula);
        }
    }
}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku a)
// Predmety jsou reprezentovany cisly 0, 1, ..., num_of_subjects-1
// Semestry jsou reprezentovany cisly 0, 1, ..., num_of_semesters-1
void each_subject_enrolled_at_least_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {

        Clause *subject_clause = create_new_clause(num_of_subjects, num_of_semesters);

        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {

            add_literal_to_clause(subject_clause, true, subject_i, semester_j);

        }

        add_clause_to_formula(subject_clause, formula);

    }

}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku b)
// Predmety jsou reprezentovany cisly 0, 1, ..., num_of_subjects-1
// Semestry jsou reprezentovany cisly 0, 1, ..., num_of_semesters-1
void each_subject_enrolled_at_most_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {

        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {

            for (unsigned semester_k = semester_j + 1; semester_k < num_of_semesters; ++semester_k) {

                Clause *subject_clause = create_new_clause(num_of_subjects, num_of_semesters);

                add_literal_to_clause(subject_clause, false, subject_i, semester_j);
                add_literal_to_clause(subject_clause, false, subject_i, semester_k);

                add_clause_to_formula(subject_clause, formula);

            }

        }

    }

}

// Tato funkce by mela do formule pridat klauzule predstavujici podminku c)
// Promenna prerequisities obsahuje pole s poctem prvku rovnym num_of_prerequisities
// Predmety jsou reprezentovany cisly 0, 1, ..., num_of_subjects-1
// Semestry jsou reprezentovany cisly 0, 1, ..., num_of_semesters-1
void add_prerequisities_to_formula(CNF *formula, Prerequisity *prerequisites, unsigned num_of_prerequisites, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(prerequisites != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned i = 0; i < num_of_prerequisites; ++i) {

        Clause *clause = create_new_clause(num_of_subjects, num_of_semesters);

        if (prerequisites[i].later_subject == 0 || prerequisites[i].later_subject == num_of_semesters) {

            add_clause_to_formula(clause, formula);
            continue;

        }

        for (unsigned j = 0; j < num_of_semesters; ++j) {

            add_literal_to_clause(clause, false, prerequisites[i].later_subject, j);

        }

        add_literal_to_clause(clause, true, prerequisites[i].earlier_subject, i);

        add_clause_to_formula(clause, formula);

    }

}




