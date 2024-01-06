# sumplete
## About this repository
This repository is dedicated to the implementation of a game developed as assignment for the introduction to programming course of the computer science course at UFOP (Universidade Federal de Ouro Preto).

## The game
The Sumplete game was originally created with ChatGPT through some chatbot prompts. You can try out the [web version of the game](https://sumplete.com/) via this link, where you can also learn more about the creation process in the [About](https://sumplete.com/about/) section.

### How to play
In Sumplete you have a board composed of an n by n matrix where each row and column has a "sum clue" associated with it. This clue tells you the sum of the numbers in that row and column. For exemple, if the sum clue for a row/column is 16, then the numbers in that row/column must add up to 16.

The cells of the board have tree different states: **Unkown**, **Keep** and **Deleted**. By default, all the cells are in the Unkown state. Your goal is to identify which cells to delete and which to keep to ensure that the sum in each column and row matches its corresponding "sum clue".