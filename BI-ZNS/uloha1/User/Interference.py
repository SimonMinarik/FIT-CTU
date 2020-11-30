from typing import List

from ExpertSystem.Business.UserFramework import IInference
from ExpertSystem.Structure.Enums import LogicalOperator
from ExpertSystem.Structure.RuleBase import Rule, Fact, ExpressionNode, Expression
from User import ActionBase


class Inference(IInference):
    """
    | User definition of the inference. You can define here you interference method (forward or backward).
      You can have here as many functions as you want, but you must implement interfere with same signature

    |
    | `def interfere(self, knowledge_base: List[Fact], rules: List[Rule], action_base: ActionBase):`
    |

    | Method `interfere` will be called each turn or manually with `Interference` button.
    | Class have no class parameters, you can use only interference parameters

    """


    def __init__(self):
        self.knowledge_base = None
        self.action_base = None


    def infere(self, knowledge_base: List[Fact], rules: List[Rule], action_base: ActionBase) -> None:
        """
        User defined interference

        :param knowledge_base: - list of Fact classes defined in  KnowledgeBase.create_knowledge_base()
        :param rules:  - list of rules trees defined in rules file.
        :param action_base: - instance of user action base for executing conclusions

        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        !!    TODO: Write implementation of your inference mechanism definition HERE    !!
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        """
        self.knowledge_base = knowledge_base
        self.action_base = action_base

        for rule in rules:
            condition = self.rule_evaluation(rule.condition)

            if condition and rule.conclusion.value in self.action_base:
                _ = self.action_base[rule.conclusion.value]


    def rule_evaluation(self, root_node: ExpressionNode) -> bool:
        """
        Example of rule tree evaluation. This implementation did not check comparision operators and uncertainty.
        For usage in interference extend this function

        :param root_node: root node of the rule tree
        :return: True if rules is satisfiable, False in case of not satisfiable or missing Facts
        """
        if root_node.value == LogicalOperator.AND:
            return self.rule_evaluation(root_node.left) and self.rule_evaluation(root_node.right)

        elif root_node.value == LogicalOperator.OR:
            return self.rule_evaluation(root_node.left) or self.rule_evaluation(root_node.right)

        elif isinstance(root_node.value, Expression):
            try:
                return self.knowledge_base[self.knowledge_base.index(root_node.value.name)](*root_node.value.args)
            except ValueError:
                return False

        else:
            return bool(root_node.value)
