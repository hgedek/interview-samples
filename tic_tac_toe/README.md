# Introduction

Sample tic-tac-toe project for qt company interview

# Types

## Board

tic-tac-toe game board model. It includes cell models and handle cell access and updates

## Form

ui component. it's developed with qt widget. qtablewidget is used for tic - tac - toe board model view.
qt has view-moel-delegate pattern for model based development but for this small example using widget was easier.

## Game

model of each new game in application. wrapper of board and manages board relations activites.

## GameManager

manager of view. its layer object between view and others [game, player]
it manages view to others and others to others

## Player

game has 2 players [ user & computer ]. 

## Strategy

computer player has strategies. for now defensive [O] and offensive [X] playing strategies implemented [simple]
at each turn computer player changes its strategy and its playing is randomized

# Methods

in example different patterns are used to make app a little bit rich

- template
- singleton
- factory method
- wrapper
- proxy / adapter

# Tests

using catch2 tests are implemented for suitable methods

to activate it in pro file TESTING macro should be activated

