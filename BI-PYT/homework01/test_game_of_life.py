import game_of_life as gol


def test_rules1():
    assert set() == gol.update({(1, 1)}, (3, 3), 1)


def test_rules2():
    target = {(1, 0), (1, 1), (1, 2)}
    assert target == gol.update({(0, 1), (1, 1), (2, 1)}, (3, 3), 1)


def test_rules3():
    target = {(0, 1), (1, 1), (2, 1)}
    assert target == gol.update(target, (3, 3), 2)


def test_rules4():
    target = {(0, 1), (0, 2), (0, 3), (1, 1), (1, 3), (2, 1), (2, 2), (2, 3)}
    assert target == gol.update({(0, 2), (1, 1), (1, 2), (1, 3), (2, 2)}, (4, 4), 1)


def test_draw1():
    target = """
+---+
|   |
|   |
|   |
+---+
"""
    output = gol.draw(set(), (3, 3))
    assert output == target[1:-1]


def test_draw2():
    target = """
+---+
|   |
| X |
|  X|
|X  |
+---+
"""
    output = gol.draw({(1, 1), (2, 2), (3, 0)}, (4, 3))
    assert output == target[1:-1]
