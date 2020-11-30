from typing import List

from ExpertSystem.Business.UserFramework import IInference, ActionBaseCaller
from ExpertSystem.Structure.Enums import LogicalOperator, Operator
from ExpertSystem.Structure.RuleBase import Rule, Fact, ExpressionNode, Expression


class Inference(IInference):
    """
    | User definition of the inference. You can define here you inference method (forward or backward).
      You can have here as many functions as you want, but you must implement interfere with same signature

    |
    | `def interfere(self, knowledge_base: List[Fact], rules: List[Rule], action_base: ActionBase):`
    |

    | Method `interfere` will be called each turn or manually with `Inference` button.
    | Class have no class parameters, you can use only inference parameters

    """
    knowledge_base: List[Fact]
    action_base: ActionBaseCaller

    def infere(self, knowledge_base: List[Fact], rules: List[Rule], action_base: ActionBaseCaller) -> None:
        """
        User defined inference

        :param knowledge_base: - list of Fact classes defined in  KnowledgeBase.create_knowledge_base()
        :param rules:  - list of rules trees defined in rules file.
        :param action_base: - instance of ActionBaseCaller for executing conclusions

        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        !!    TODO: Write implementation of your inference mechanism definition HERE    !!
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        """
        self.knowledge_base = knowledge_base
        self.action_base = action_base

        for rule in rules:
            condition = self.rule_evaluation(rule.condition)
            condition_cf = self.uncertainty_evaluation(rule.condition)

            if not rule.uncertainty:
                rule.uncertainty = 1
            if condition:
                print(f'conc: {condition_cf} and rule: {rule.uncertainty}')
                condition_cf *= rule.uncertainty
                if condition_cf > 0.1:
                    print(f'ide tooooooooooooooooooo')
                    self.conclusion_evaluation(rule.conclusion)
                #print(f'Rule {rule} has uncertainty {condition_cf}')

    def uncertainty_evaluation(self, root_node: ExpressionNode) -> float:

        if root_node.operator == LogicalOperator.AND:
            return min(self.uncertainty_evaluation(root_node.left), self.uncertainty_evaluation(root_node.right))

        if root_node.operator == LogicalOperator.OR:
            return max(self.uncertainty_evaluation(root_node.left), self.uncertainty_evaluation(root_node.right))

        elif isinstance(root_node.value, Expression):
            if root_node.value.uncertainty:
                exp_cf = root_node.value.uncertainty
                if self.knowledge_base[self.knowledge_base.index(root_node.value.name)].probability:
                    exp_cf *= self.knowledge_base[self.knowledge_base.index(root_node.value.name)].probability
            elif self.knowledge_base[self.knowledge_base.index(root_node.value.name)].probability:
                exp_cf = self.knowledge_base[self.knowledge_base.index(root_node.value.name)].probability
            else:
                exp_cf = 1
            return exp_cf

    def rule_evaluation(self, root_node: ExpressionNode) -> bool:
        """
        Example of rule tree evaluation. This implementation did not check comparision operators and uncertainty.
        For usage in inference extend this function

        :param root_node: root node of the rule tree
        :return: True if rules is satisfiable, False in case of not satisfiable or missing Facts
        """
        if root_node.operator == LogicalOperator.AND:
            return self.rule_evaluation(root_node.left) and self.rule_evaluation(root_node.right)

        elif root_node.operator == LogicalOperator.OR:
            return self.rule_evaluation(root_node.left) or self.rule_evaluation(root_node.right)

        elif isinstance(root_node.value, Expression):
            try:
                """ == """
                if root_node.value.comparator == Operator.EQUAL:
                    return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args) \
                           == root_node.value.value
                """ < """
                if root_node.value.comparator == Operator.LESS_THEN:
                    return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args) \
                           < float(root_node.value.value)
                """ > """
                if root_node.value.comparator == Operator.MORE_THEN:
                    return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args) \
                           > float(root_node.value.value)
                """ != """
                if root_node.value.comparator == Operator.NOT_EQUAL:
                    return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args) \
                           != root_node.value.value
                """ <= """
                if root_node.value.comparator == Operator.LESS_EQUAL:
                    return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args) \
                           <= float(root_node.value.value)
                """ >= """
                if root_node.value.comparator == Operator.MORE_EQUAL:
                    return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args) \
                           >= float(root_node.value.value)

                return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args)
            except ValueError:
                return False

        else:
            return bool(root_node.value)

    def conclusion_evaluation(self, root_node: ExpressionNode):
        if self.action_base.has_method(root_node.value):
            self.action_base.call(root_node.value)
