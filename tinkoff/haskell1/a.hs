findValue :: [a] -> (a -> Bool) -> Maybe a
findValue [] y = Nothing
findValue (x:xs) f | f x    = Just x
                   | otherwise = findValue xs f
data IntList = Null | Cons Int IntList deriving Show

instance Eq IntList where
    (==) Null Null                 = True
    (==) (Cons x xs) (Cons x' xs') = (==) x x' && (==) xs xs'
    (==) _ _                       = False

data Tree a = Nil | Node a (Tree a) (Tree a) deriving Show

instance Functor Tree where
    fmap _ Nil          = Nil
    fmap f (Node a b c) = Node (f a) (fmap f b) (fmap f c)