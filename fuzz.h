
#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

//Fuzzy object
Fuzzy *fuzzy = new Fuzzy();

void fuzzy_logic_init(){

  // fuzzy sets
  // turbidity
  FuzzySet *exelT = new FuzzySet(5, 10, 20, 30);
  FuzzySet *gutT = new FuzzySet(120, 30, 40, 50);
  FuzzySet *badT = new FuzzySet(40, 50, 100, 150);

  //Electrical conductivity
  FuzzySet *exelE = new FuzzySet(0.5, 1.0, 1.5, 2.0);
  FuzzySet *gutE = new FuzzySet(1.5, 2.0, 2.5, 3.0);
  FuzzySet *badE = new FuzzySet(2.5, 3.0, 5.0, 6.0);

  // Water Temperature
    FuzzySet *coldT = new FuzzySet(0, 0, 20, 30);
    FuzzySet *moderateT = new FuzzySet(20, 30, 45, 55);
    FuzzySet *warmT = new FuzzySet(45, 55, 75, 75);


  //water Q
  FuzzySet *exelW = new FuzzySet(70, 80, 100, 100);
  FuzzySet *gutW= new FuzzySet(30, 50, 70, 80);
  FuzzySet *badW = new FuzzySet(0, 0, 30, 50);

  //variables 
  //turbidity variables
  FuzzyInput *turbidity= new FuzzyInput(1);
  turbidity->addFuzzySet(exelT);
  turbidity->addFuzzySet(gutT);
  turbidity->addFuzzySet(badT);
  fuzzy->addFuzzyInput(turbidity);

  //Electrical conductivity
  FuzzyInput *ec= new FuzzyInput(2);
  ec->addFuzzySet(exelE);
  ec->addFuzzySet(gutE);
  ec->addFuzzySet(badE);
  fuzzy->addFuzzyInput(ec);
  
  // Water Temperature
  FuzzyInput *waterTemperature = new FuzzyInput(3);
  waterTemperature->addFuzzySet(coldT);
  waterTemperature->addFuzzySet(moderateT);
  waterTemperature->addFuzzySet(warmT);
  fuzzy->addFuzzyInput(waterTemperature);


 
  //water  Quality
  FuzzyOutput *water = new FuzzyOutput(1);
  water->addFuzzySet(exelW);
  water->addFuzzySet(gutW);
  water->addFuzzySet(badW);
  fuzzy->addFuzzyOutput(water);

  //rules FuzzyLogic
  // rule1: if turbidity and EC are Excellecnt water Q is excellent
  FuzzyRuleAntecedent *rule1 =new FuzzyRuleAntecedent();
  rule1->joinWithAND(exelT,exelE);
 //  rule1->joinWithAND(coldT);
  FuzzyRuleConsequent *waterEx = new FuzzyRuleConsequent();
  waterEx->addOutput(exelW);
  FuzzyRule *fuzzyRule1 =new FuzzyRule(1,rule1,waterEx);
  fuzzy->addFuzzyRule(fuzzyRule1);

  //rule2: if tub and Ec are good water Q is goood
  FuzzyRuleAntecedent *rule2 =new FuzzyRuleAntecedent();
  rule2->joinWithAND(gutT,gutE);
  //rule2->joinWithAND(moderateT);
  FuzzyRuleConsequent *watergut = new FuzzyRuleConsequent();
  watergut->addOutput(gutW);
  FuzzyRule *fuzzyRule2 =new FuzzyRule(2,rule2,watergut);
  fuzzy->addFuzzyRule(fuzzyRule2);

  //rule3 :if tub is good but Ec is ecclent water Q is good
  FuzzyRuleAntecedent *rule3 =new FuzzyRuleAntecedent();
  rule3->joinWithAND(gutT,exelE);
  //rule2->joinWithAND(moderateT);
  FuzzyRuleConsequent *watergut2 = new FuzzyRuleConsequent();
  watergut2->addOutput(gutW);
  FuzzyRule *fuzzyRule3 =new FuzzyRule(3,rule3,watergut2);
  fuzzy->addFuzzyRule(fuzzyRule3);

  //rule 4 : if tub is excellent and Ec is good the water is good
  FuzzyRuleAntecedent *rule4 =new FuzzyRuleAntecedent();
  rule4->joinWithAND(gutE,exelT);
 // rule4->joinWithAND(moderateT);
  FuzzyRuleConsequent *watergut3 = new FuzzyRuleConsequent();
  watergut3->addOutput(gutW);
  FuzzyRule *fuzzyRule4 =new FuzzyRule(4,rule4,watergut3);
  fuzzy->addFuzzyRule(fuzzyRule4);

  //rule 5: if tub is bad water Q is bad
  FuzzyRuleAntecedent *rule5 =new FuzzyRuleAntecedent();
  rule5->joinSingle(badT);
  FuzzyRuleConsequent *watergut4 = new FuzzyRuleConsequent();
  watergut4->addOutput(badW);
  FuzzyRule *fuzzyRule5 =new FuzzyRule(5,rule5,watergut4);
  fuzzy->addFuzzyRule(fuzzyRule5);

  //rule 6 : if EC is bad water Q is bad
  FuzzyRuleAntecedent *rule6 =new FuzzyRuleAntecedent();
  rule6->joinSingle(badE);
  FuzzyRuleConsequent *watergut5 = new FuzzyRuleConsequent();
  watergut5->addOutput(badW);
  FuzzyRule *fuzzyRule6 =new FuzzyRule(6,rule6,watergut5);
  fuzzy->addFuzzyRule(fuzzyRule6);

  //rule 7 waarm water bad water
  FuzzyRuleAntecedent *rule7 =new FuzzyRuleAntecedent();
  rule7->joinSingle(warmT);
  FuzzyRuleConsequent *watergut6 = new FuzzyRuleConsequent();
  watergut6->addOutput(badW);
  FuzzyRule *fuzzyRule7 =new FuzzyRule(7,rule7,watergut6);
  fuzzy->addFuzzyRule(fuzzyRule7);
}


float fuzzy_result (float tub,float ec,float t)
{
  // fuzzyfication
  fuzzy->setInput(1, tub); 
  fuzzy->setInput(2, ec); 
  fuzzy->setInput(3,t);
  fuzzy->fuzzify();

  // defuzzyfication
  float output = fuzzy->defuzzify(1); 

  return output;
}














