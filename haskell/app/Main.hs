module Main where

import qualified MyLib (someFunc)

-- data Either a b = Left a | Right b

type X a = Either a a

main :: IO ()
main = do
  putStrLn "Hello, Haskell!"
  MyLib.someFunc