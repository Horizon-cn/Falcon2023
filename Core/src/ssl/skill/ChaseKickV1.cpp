��# i n c l u d e   " C h a s e K i c k V 1 . h " 
 
 # i n c l u d e   " G D e b u g E n g i n e . h " 
 
 # i n c l u d e   < V i s i o n / V i s i o n M o d u l e . h > 
 
 # i n c l u d e   " F a c t o r y . h " 
 
 # i n c l u d e   < u t i l s . h > 
 
 # i n c l u d e   < M o t i o n C o n t r o l / C o n t r o l M o d e l . h > 
 
 # i n c l u d e   < c o r n e l l / T r a j e c t o r y . h > 
 
 # i n c l u d e   < W o r l d M o d e l / R o b o t C a p a b i l i t y . h > 
 
 # i n c l u d e   < M o t i o n C o n t r o l / C M m o t i o n . h > 
 
 # i n c l u d e   < R o b o t S e n s o r . h > 
 
 # i n c l u d e   " u t i l s . h " 
 
 # i n c l u d e   " S h o o t R a n g e L i s t . h " 
 
 
 
 # i n c l u d e   < C o m m a n d F a c t o r y . h > 
 
 
 
 # i n c l u d e   " P o i n t C a l c u l a t i o n / T o u c h K i c k P o s . h " 
 
 # i n c l u d e   " B a l l S p e e d M o d e l . h " 
 
 # i n c l u d e   < G D e b u g E n g i n e . h > 
 
 # i n c l u d e   " W o r l d M o d e l / D r i b b l e S t a t u s . h " 
 
 # i n c l u d e   < s s l / P a r a m M a n a g e r N e w . h > 
 
 
 
 n a m e s p a c e 
 
 { 
 
 	 / /   �J\����e�b��e�b��Y�lO��w�a�b��e�b
 
 	 i n t   T R A J E C T O R Y _ M E T H O R D   =   1 ; 
 
 
 
 	 e n u m { 
 
 	 	 R U S H _ T O _ B A L L   =   1 , 	 / /   ��e�b��R�c�e�b��e�b
 
 	 	 W A I T _ B A L L   =   2 , 	 	 / /   �z����b��e�b��e�bMR
 
 	 	 F O L L O W _ B A L L   =   3 , 	 / /   ��e�b��e�b��e�b��e�b��e�b
 
 	 	 G O _ K I C K _ B A L L   =   4 	 / /   ��e�bMR��e�b��e�b��e�b
 
 	 } ; 
 
 
 
 	 / /   �r`��SO�b��e�bGN��e�b���
 
 	 c o n s t   d o u b l e   R U S H _ T O _ B A L L _ C R I T I C A L _ D I S T   =   1 0 0 ; 	 / /   1 0 0 c m 
 
 	 c o n s t   d o u b l e   F O L L O W B A L L _ C R I T I C A L _ D I S T   =   5 0 ; 	 	 / /   5 0 c m 
 
 	 c o n s t   d o u b l e   G O _ K I C K _ B A L L _ C R I T I C A L _ D I S T   =   2 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E ; 
 
 
 
 	 / /   ��e�b��e�bp���e�b!j�u��v��b��e�b
 
 	 c o n s t   d o u b l e   S T E P _ T I M E   =   1 . 0 / P a r a m : : V i s i o n : : F R A M E _ R A T E ; 
 
 
 
 	 / /   ����e�b��e�b���
 
 	 c o n s t   d o u b l e   M A X _ T I M E   =   5 ;   / /   �K{���e�b��e�b�e��e�b( / s ) 
 
 	 d o u b l e   C M _ P R E D I C T _ F A C T O R   =   1 . 5 ; 
 
 	 c o n s t   d o u b l e   B a l l _ M o v i n g _ F a s t _ S p e e d   =   5 0 ; 	 / /   �S��e�b:N1 m / s ��e�b��e�b���i��b:N5 0 c m / s 
 
         / / 
 
 	 c o n s t   d o u b l e   s p e e d _ f a c t o r   =   0 . 7 ; 
 
 
 
 	 b o o l   D E B U G _ E N G I N E   =   0 ; 
 
 
 
 	 d o u b l e   C H A S E K I C K _ T O P E N A L T Y _ G A P   =   1 0 ; 
 
 	 d o u b l e   C H A S E K I C K _ E N D V E L _ S T A R T X   =   0 ; 
 
 	 d o u b l e   C H A S E K I C K _ M A X E N D V E L   =   3 5 0 ; 
 
 	 C G e o P o i n t   G O A L _ L E F T _ P O S   =   C G e o P o i n t ( P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2 ,   - P a r a m : : F i e l d : : G O A L _ W I D T H   /   2   ) ;         / / ��e�b��e�b��e�b��e�b����a�b��e�b
 
 	 C G e o P o i n t   G O A L _ R I G H T _ P O S   =   C G e o P o i n t ( P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2 ,   P a r a m : : F i e l d : : G O A L _ W I D T H   /   2 ) ; 
 
 	 C G e o P o i n t   G O A L _ C E N T R E _ P O S   =   C G e o P o i n t ( P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2 ,   0 ) ;   
 
 } 
 
 
 
 C C h a s e K i c k V 1 : : C C h a s e K i c k V 1 ( ) 
 
 { 
 
         C H A S E K I C K _ T O P E N A L T Y _ G A P   =   P a r a m M a n a g e r : : I n s t a n c e ( ) - > C H A S E K I C K _ T O P E N A L T Y _ G A P ; 
 
         C H A S E K I C K _ E N D V E L _ S T A R T X   =   P a r a m M a n a g e r : : I n s t a n c e ( ) - > C H A S E K I C K _ E N D V E L _ S T A R T X ; 
 
         C H A S E K I C K _ M A X E N D V E L   =   P a r a m M a n a g e r : : I n s t a n c e ( ) - > C H A S E K I C K _ M A X E N D V E L ; 
 
         D E B U G _ E N G I N E   =   P a r a m M a n a g e r : : I n s t a n c e ( ) - > C h a s e K i c k _ D e b u g ; 
 
 	 _ d i r e c t C o m m a n d   =   N U L L ; 
 
 	 _ l a s t C y c l e   =   0 ; 
 
 } 
 
 
 
 v o i d   C C h a s e K i c k V 1 : : p l a n ( c o n s t   C V i s i o n M o d u l e *   p V i s i o n ) 
 
 { 
 
 	 / /   ��y�e�b��,gs k i l l ��e�b:N��e�b�Y�r`��e�b��e�bB E G I N N I N G ��e�b��e�b����e�b N�N��e�b��e�b��e�b��e�b
 
 	 i f   (   p V i s i o n - > C y c l e ( )   -   _ l a s t C y c l e   >   P a r a m : : V i s i o n : : F R A M E _ R A T E   *   0 . 1   ) { 
 
 	 	 s e t S t a t e ( B E G I N N I N G ) ; 
 
 	 } 
 
 
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 / * 1 . ��e�b��e�b��e�bp���e�b!j��e�b:N��e�b��e�b��e�b��e�b��S�x�b��e�b!j���*   :��e�b��e�b�S��e�b��e�bs^��e�b��e�b��e�b�l��S!S�b��e�bl���e�b��e�b  * 	 
 
 	 ��e�b�Sx m l ��e�b��e�b��w�x�b\��e�b�R���b��e�b��e�b��e�b��e�b�F}m n i A u t o 	 	 	 	 	 	 	 * / 
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 _ d i r e c t C o m m a n d   =   N U L L ; 
 
 	 c o n s t   B a l l V i s i o n T &   b a l l   =   p V i s i o n - > B a l l ( ) ; 
 
 	 c o n s t   i n t   r o b o t N u m   =   t a s k ( ) . e x e c u t o r ; 
 
 	 c o n s t   P l a y e r V i s i o n T &   m e   =   p V i s i o n - > O u r P l a y e r ( r o b o t N u m ) ; 
 
 	 c o n s t   i n t   p l a y e r F l a g   =   t a s k ( ) . p l a y e r . f l a g ; 
 
 	 c o n s t   b o o l   n e e d D r i b b l e   =     p l a y e r F l a g   &   P l a y e r S t a t u s : : D R I B B L I N G ; 
 
 	 i f   ( n e e d D r i b b l e ) { 
 
 	 	 D r i b b l e S t a t u s : : I n s t a n c e ( ) - > s e t D r i b b l e C o m m a n d ( r o b o t N u m ,   2 ) ; 
 
 	 } 
 
 
 
 	 c o n s t   C R o b o t C a p a b i l i t y *   r o b o t C a p   =   R o b o t C a p F a c t o r y : : I n s t a n c e ( ) - > g e t R o b o t C a p ( p V i s i o n - > S i d e ( ) ,   r o b o t N u m ) ; 
 
 	 c o n s t   d o u b l e   M a x S p e e d   =   r o b o t C a p - > m a x S p e e d ( 0 ) ; 	 	 	 	 	 	 	 	 / / s p e e d 
 
 	 c o n s t   d o u b l e   M a x A c c e l e r a t i o n   =   r o b o t C a p - > m a x A c c e l e r a t i o n ( C V e c t o r ( 0 , 0 ) , 0 ) ; 	 / / a c c e l e r a t i o n 
 
 	 
 
 	 C G e o P o i n t   b a l l _ p r e d i c t _ p o s   =   b a l l . P o s ( ) ; 
 
 	 c o n s t   d o u b l e   b a l l V e l D i r   =   b a l l . V e l ( ) . d i r ( ) ; 
 
 	 d o u b l e   b a l l _ t i m e   =   0 ; 
 
 	 d o u b l e   b a l l _ s p e e d   =   b a l l . V e l ( ) . m o d ( ) ; 
 
 	 d o u b l e   r o b o t _ t i m e   =   0 . 0 ; 
 
 	 i n t   i n c r e a s e _ s t e p   =   5 ; 
 
 
 
 	 c o n s t   d o u b l e   d i s t b a l l 2 m e   =   b a l l . P o s ( ) . d i s t ( m e . P o s ( ) ) ; 
 
 	 d o u b l e   r o b o t _ a h e a d _ t i m e   =   0 . 2 ; 
 
 	 i f (   d i s t b a l l 2 m e   >   1 5 0   ) { 	 	 / / T O D O 
 
 	 	 r o b o t _ a h e a d _ t i m e   =   0 . 0 5 ; 
 
 	 } e l s e   i f (   d i s t b a l l 2 m e   >   7 5   ) { 
 
 	 	 r o b o t _ a h e a d _ t i m e   =   0 . 0 ; 
 
 	 } e l s e { 
 
 	 	 r o b o t _ a h e a d _ t i m e   =   - 0 . 1 0 ; 
 
 	 } 
 
 
 
 	 P l a y e r C a p a b i l i t y T   c a p a b i l i t y ; 
 
 	 c a p a b i l i t y . m a x A c c e l   =   c a p a b i l i t y . m a x D e c   =   M a x A c c e l e r a t i o n ; 
 
 	 c a p a b i l i t y . m a x S p e e d   =   c a p a b i l i t y . m a x S p e e d X   =   c a p a b i l i t y . m a x S p e e d Y   =   M a x S p e e d ; 
 
 	 
 
 
 
 	 / /   !j��e�b��e�b��e�b��v�0�b��Y�S�e��e�b:   1 - \��e�b��e�b��e�b��e�b2 - ��e�b����e�b��e�b; 3 - ��e�b�e��e�b��e�b��e�b��~�a�b���
 
 	 l o n g   p r e d i c t _ c y c l e = 0 ; 
 
 	 d o { 
 
 	 	 b a l l _ p r e d i c t _ p o s   =   B a l l S p e e d M o d e l : : I n s t a n c e ( ) - > p o s F o r T i m e ( p r e d i c t _ c y c l e , p V i s i o n ) ; 
 
 	 	 p r e d i c t _ c y c l e + = i n c r e a s e _ s t e p ; 
 
 	 	 b a l l _ t i m e   + =   i n c r e a s e _ s t e p * S T E P _ T I M E ; 
 
 	 	 C G e o P o i n t   t m p P o i n t   =   b a l l _ p r e d i c t _ p o s   +   U t i l s : : P o l a r 2 V e c t o r ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R , U t i l s : : N o r m a l i z e ( t a s k ( ) . p l a y e r . a n g l e + P a r a m : : M a t h : : P I ) ) ; 
 
 	 	 
 
 	 	 i f (   C M U _ T R A J   = =   T R A J E C T O R Y _ M E T H O R D   ) 	 / / C M U ��e�b��e�b��R�x�b��e�b�eO��b��e�b���
 
 	 	 	 r o b o t _ t i m e   =   e x p e c t e d C M P a t h T i m e ( m e ,   t m p P o i n t ,   c a p a b i l i t y ,   C V e c t o r ( 0 ,   0 ) ,   C M _ P R E D I C T _ F A C T O R ,   0 )   +   S T E P _ T I M E * P a r a m : : L a t e n c y : : T O T A L _ L A T E D _ F R A M E ; 
 
 	 	 e l s e 
 
 	 	 	 r o b o t _ t i m e   =   e x p e c t e d P a t h T i m e ( m e , t m p P o i n t ,   M a x A c c e l e r a t i o n ,   M a x S p e e d )   +   S T E P _ T I M E * P a r a m : : L a t e n c y : : T O T A L _ L A T E D _ F R A M E ; 
 
 	 } w h i l e   (   r o b o t _ t i m e   +   r o b o t _ a h e a d _ t i m e   >   b a l l _ t i m e     & &   ! U t i l s : : O u t O f F i e l d ( b a l l _ p r e d i c t _ p o s )   
 
 	 	 & &   r o b o t _ t i m e   < =   M A X _ T I M E   & &   b a l l _ t i m e   < =   M A X _ T I M E ) ; 
 
 
 
 	 / / ��e�b��e�b��e�b���
 
 	 c o n s t   d o u b l e   c a l _ t i m e   =     r o b o t _ t i m e ; 	 	 	 	 / / �e��e�b
 
 	 c o n s t   C G e o P o i n t   p r e d i c t _ p o s B a l l   =   b a l l _ p r e d i c t _ p o s ; 	 / / ����e�b���
 
 	 c o n s t   d o u b l e   d i s t _ r a w b a l l 2 p r e d i c t b a l l   =   b a l l . P o s ( ) . d i s t ( b a l l _ p r e d i c t _ p o s ) ; 	 / / �S�Y��Y0R����e�b��e�b��e�b
 
 
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 / /   2 . ��e�bMR��e�b��e�b��e�bo`��e�b��e�b����e�b�V��e�b��e�bo`
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 c o n s t   d o u b l e   m e S p e e d   =   m e . V e l ( ) . m o d ( ) ; 
 
 	 c o n s t   d o u b l e   f i n a l K i c k D i r   =   t a s k ( ) . p l a y e r . a n g l e ; 	 	 	 	 	 	 	 	 	 / / ��e�b��w�x�b��e�b��e�b��e�b
 
 	 c o n s t   C V e c t o r   s e l f 2 b a l l   =   p r e d i c t _ p o s B a l l   -   m e . P o s ( ) ; 	 	 	 	 	 	 	 	 / / \��e�b��e�b����e�b��e�b��e�b��e�b
 
 	 c o n s t   C V e c t o r   s e l f 2 r a w b a l l   =   b a l l . P o s ( )   -   m e . P o s ( ) ; 	 	 	 	 	 	 	 	 	 / / \��e�b��e�b��e�bMR��e�b��e�b��e�b
 
 	 c o n s t   C V e c t o r   s e l f 2 g o a l   =   G O A L _ C E N T R E _ P O S   -   m e . P o s ( ) ; 	 	 	 	 	 	 	 	 / / \��e�b��e�b��e�b��e�b��e�b��e�b��e�b��e�b
 
 	 c o n s t   C V e c t o r   b a l l 2 g o a l   =   G O A L _ C E N T R E _ P O S   -   b a l l . P o s ( ) ; 	 	 	 	 	 	 	 	 / / ��e�b��e�b��e�b��e�b��e�b��e�b��e�b
 
 	 c o n s t   C V e c t o r   b a l l 2 g o a l L e f t   =   G O A L _ L E F T _ P O S   -   b a l l . P o s ( ) ; 	 	 	 	 	 	         / / ��e�b��e�b��e�b����a�b��e�b��e�b��e�b
 
 	 c o n s t   C V e c t o r   b a l l 2 g o a l R i g h t   =   G O A L _ R I G H T _ P O S   -   b a l l . P o s ( ) ; 	 	 	 	 	 	         / / ��e�b��e�b��e�b����a�b��e�b��e�b��e�b
 
 	 c o n s t   d o u b l e   d i s t 2 p r e d i c t b a l l   =   s e l f 2 b a l l . m o d ( ) ; 	 	 	 	 	 	 	 	 	 / / \��e�b��e�b����e�b��e�b��e�b���
 
 	 c o n s t   d o u b l e   d i s t 2 b a l l   =   s e l f 2 r a w b a l l . m o d ( ) ; 	 	 	 	 	 	 	 	 	 	 / / \��e�b��e�b��e�bMR��e�b��e�b���
 
 	 c o n s t   d o u b l e   r e v e r s e _ f i n a l D i r   =   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r + P a r a m : : M a t h : : P I ) ; 	 	 / / ��e�b��e�b��e�b��e�b��e�b�Y��e�b���
 
 	 c o n s t   d o u b l e   r e v e r s e _ B a l l V e l D i r   =   U t i l s : : N o r m a l i z e ( b a l l . V e l ( ) . d i r ( )   -   P a r a m : : M a t h : : P I ) ; 	 	 / / ��e�b��R�Q�b��e�b�Y��e�b���
 
 	 c o n s t   d o u b l e   d A n g D i f f   =   U t i l s : : N o r m a l i z e ( s e l f 2 b a l l . d i r ( ) - f i n a l K i c k D i r ) ; 
 
 	 c o n s t   d o u b l e   d A n g D i f f R a w   =   U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - f i n a l K i c k D i r ) ; 	 	 / / \��e�b��e�b��e�bMR��e�b  -   ��e�b��e�b��e�b  ��S�e�b	 T S B 
 
 	 c o n s t   C V e c t o r   b a l l V e l   =   b a l l . V e l ( ) ; 
 
 	 c o n s t   d o u b l e   b a l l S p e e d   =   b a l l V e l . m o d ( ) ; 
 
 	 b o o l   i s B a l l S p e e d F a s t   =   ( b a l l S p e e d   > =   B a l l _ M o v i n g _ F a s t _ S p e e d ) ? t r u e : f a l s e ; 	 	 / / ��e�b��e�b�P�[��e�b��e�b<P��S���b��e�b��e�b�҉�Q�b��YY��e�b
 
 
 
 	 d o u b l e   a l l o w I n f r o n t A n g l e B u f f e r   =   ( d i s t 2 b a l l / ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E ) ) * P a r a m : : V e h i c l e : : V 2 : : K I C K _ A N G L E   <   P a r a m : : M a t h : : P I / 5 . 0 ? 
 
 	 	 	 	 	 	 	 	 	 	 ( d i s t 2 b a l l / ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E ) ) * P a r a m : : V e h i c l e : : V 2 : : K I C K _ A N G L E : P a r a m : : M a t h : : P I / 5 . 0 ; 
 
 	 b o o l   i s B a l l I n F r o n t   =   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - m e . D i r ( ) ) )   <   a l l o w I n f r o n t A n g l e B u f f e r 
 
 	 	 	 	 	 	 	 & &   d i s t 2 b a l l   <   ( 2 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E ) ; 
 
 	 b o o l   i s B a l l A t F r o n t   =   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   m e . D i r ( ) ) )   <   P a r a m : : M a t h : : P I   /   2 . 0 ;       / / ��S���b��e�b�҉�Q�b���y{�bMR
 
 	 b o o l   i s B a l l A t D i r e c t F r o n t   =   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   m e . D i r ( ) ) )   <   P a r a m : : M a t h : : P I   /   4 . 0 ;       / / ��S���b��e�b�҉�Q�b���y{�b��e�b��e�bMR��e�b��e�b��e�b�e��e�b4Y��e�b��e�b��e�b��e�bT��e�b��e�bOO��e�b
 
 	 b o o l   i s B a l l T o G o a l   =   m i n ( b a l l 2 g o a l L e f t . d i r ( ) ,   b a l l 2 g o a l R i g h t . d i r ( ) )   <   b a l l . V e l ( ) . d i r ( )   & &   b a l l . V e l ( ) . d i r ( ) <   m a x ( b a l l 2 g o a l L e f t . d i r ( ) ,   b a l l 2 g o a l R i g h t . d i r ( ) ) ;   / / ��S���b��e�b�҉�Q�b��e�b��e�b�S
 
 
 
 	 / / ��e�b��e�b��4s�b
 
 	 d o u b l e   i s S e n s o r e d   =   R o b o t S e n s o r : : I n s t a n c e ( ) - > I s I n f o V a l i d ( r o b o t N u m )   & &   R o b o t S e n s o r : : I n s t a n c e ( ) - > I s I n f r a r e d O n ( r o b o t N u m ) ; 	 / / �҉�Q�b��Swx�b~s�e�b��e�b���
 
 	 / / �V��e�b��c�d�b
 
 	 c o n s t   d o u b l e   d A n g l e M e D i r 2 F i n a l K i c k   =   f a b s ( U t i l s : : N o r m a l i z e ( m e . D i r ( ) - f i n a l K i c k D i r ) ) ; 	 	 	 	 / / ��e�bMR��e�b��e�b��e�b��e�b��e�b��e�b��e�b��S�e�b
 
 	 c o n s t   d o u b l e   d A n g l e M e B a l l 2 B a l l V e l D i r   =   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   b a l l V e l D i r ) ) ; 	 / / ��e�b��e�b��e�b��e�b��e�b��e�b��z9Y�e�b
 
 	 c o n s t   d o u b l e   d A n g l e M e B a l l 2 M e D i r   =   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   m e . D i r ( ) ) ) ; 	 	 / / ��e�b��e�b��e�b��e�b\��e�b��e�b��e�b�����
 
 	 c o n s t   d o u b l e   d A n g l e F i n a l K i c k 2 B a l l V e l D i r   =   f a b s ( U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r   -   b a l l V e l D i r ) ) ; 	 
 
 	 c o n s t   C G e o P o i n t   m y P o s   =   m e . P o s ( ) ; 
 
 	 c o n s t   C G e o L i n e   s e l f 2 t a r g e t L i n e   =   C G e o L i n e ( m y P o s , m y P o s + U t i l s : : P o l a r 2 V e c t o r ( 8 0 0 , U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ) ; 	 	 	 / / \��e�b��e�b��e�b��e�b�v��e�b��e�b�v��e�b
 
 	 c o n s t   C G e o S e g m e n t   s e l f 2 t a r g e t S e g   =   C G e o S e g m e n t ( m y P o s , m y P o s + U t i l s : : P o l a r 2 V e c t o r ( 8 0 0 , U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ) ; 
 
 	 c o n s t   C G e o L i n e   b a l l M o v i n g L i n e   =   C G e o L i n e ( b a l l . P o s ( ) , b a l l . P o s ( ) + U t i l s : : P o l a r 2 V e c t o r ( 8 0 0 , U t i l s : : N o r m a l i z e ( b a l l V e l D i r ) ) ) ; 	 	 / / ��e�b��e�b�v��e�b
 
 	 c o n s t   C G e o S e g m e n t   b a l l M o v i n g S e g   =   C G e o S e g m e n t ( b a l l . P o s ( ) , b a l l . P o s ( ) + U t i l s : : P o l a r 2 V e c t o r ( 8 0 0 , U t i l s : : N o r m a l i z e ( b a l l V e l D i r ) ) ) ; 	 
 
 	 c o n s t   C G e o S e g m e n t   b a l l M o v i n g L o n g S e g   =   C G e o S e g m e n t ( b a l l . P o s ( ) ,   b a l l . P o s ( )   +   U t i l s : : P o l a r 2 V e c t o r ( 2 0 0 0 ,   U t i l s : : N o r m a l i z e ( b a l l V e l D i r ) ) ) ;   / / ��e�b��e�b��e�b��e�b��e�b��z�kO��b��e�b��e�b��S���b����e�bo r ��e�b��e�b
 
 	 c o n s t   C G e o L i n e L i n e I n t e r s e c t i o n   s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e   =   C G e o L i n e L i n e I n t e r s e c t i o n ( s e l f 2 t a r g e t L i n e , b a l l M o v i n g L i n e ) ; 
 
 	 C G e o P o i n t   s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e _ s e c P o s   =   p r e d i c t _ p o s B a l l ; 
 
 	 i f (   s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e . I n t e r s e c t a n t ( )   ) { 
 
 	 	 s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e _ s e c P o s   =   s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e . I n t e r s e c t P o i n t ( ) ; 	 / / \��e�b��e�b�v��e�b��e�b��e�bT��e�b��e�b��e�b�SUa��e�b���
 
 	 } 
 
 	 c o n s t   b o o l   i s I n t e r s e c t i o n P o s O n s e l f 2 t a r g e t S e g   =   s e l f 2 t a r g e t S e g . I s P o i n t O n L i n e O n S e g m e n t ( s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e _ s e c P o s ) ; 	 / / ��e�b��e�b��e�b\��e�b�v��e�b��e�b�S���
 
 	 c o n s t   b o o l   i s I n t e r s e c t i o n P o s O n B a l l M o v i n g S e g   =   b a l l M o v i n g S e g . I s P o i n t O n L i n e O n S e g m e n t ( s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e _ s e c P o s ) ; 	 	 / / ��e�b��e�b��e�b��e�b��e�b��z���b
 
 	 c o n s t   C G e o P o i n t   b a l l P r o j   =   s e l f 2 t a r g e t L i n e . p r o j e c t i o n ( b a l l . P o s ( ) ) ; 
 
 	 c o n s t   b o o l   b a l l O n T a r g e t S e g   =   s e l f 2 t a r g e t S e g . I s P o i n t O n L i n e O n S e g m e n t ( b a l l P r o j ) ; 
 
 	 
 
 	 c o n s t   C G e o P o i n t   p r o j M e   =   b a l l M o v i n g S e g . p r o j e c t i o n ( m e . P o s ( ) ) ; 	 	 	 	 	 / / \��e�b��e�b��e�b��r���b��e�b����x�b�bq_��e�b
 
 	 c o n s t   C G e o P o i n t   L o n g p r o j M e   =   b a l l M o v i n g L o n g S e g . p r o j e c t i o n ( m e . P o s ( ) ) ;                                 / / \��e�b��e�b��e�b��r���b��e�b����x�b�bq_��e�b
 
 	 d o u b l e   p r o j D i s t   =   p r o j M e . d i s t ( m e . P o s ( ) ) ; 	 	 	 	 	 	 	 	 	 	 / / \��e�b��e�b�bq_��e�b(g��e�b���
 
 	 c o n s t   d o u b l e   b a l l 2 p r o j D i s t   =   p r o j M e . d i s t ( b a l l . P o s ( ) ) ; 	 	 	 	 	 	 	 / / �bq_��Y0R��e�b(g��e�b���
 
 	 c o n s t   b o o l   m e O n B a l l M o v i n g S e g   =   b a l l M o v i n g S e g . I s P o i n t O n L i n e O n S e g m e n t ( p r o j M e ) ; 	 / / �bq_��e�b�҉�Q�b��e�b��e�b��e�b��z���b��e�b��e�b
 
 	 c o n s t   b o o l   m e O n B a l l M o v i n g L o n g S e g   =   b a l l M o v i n g L o n g S e g . I s P o i n t O n L i n e O n S e g m e n t ( L o n g p r o j M e ) ; 	 / / �bq_��e�b�҉�Q�b��e�b��e�b��Ry{�b��z���b��e�b��e�b
 
 
 
 	 c o n s t   d o u b l e   d A n g e M e V e l 2 B a l l V e l   =   U t i l s : : N o r m a l i z e ( m e . V e l ( ) . d i r ( ) - b a l l V e l D i r ) ; 	 	 	 / / \��e�b��R�^�Q�b��e�b��e�b��e�b�O��e�b��O9Y�e�b
 
 	 c o n s t   d o u b l e   d S p e e d M e 2 B a l l   =   f a b s ( b a l l S p e e d   -   m e . V e l ( ) . m o d ( ) * c o s ( d A n g e M e V e l 2 B a l l V e l ) ) ; 	 / / ��e�b��e�b��e�b��e�b��z�Q�b��e�b��e�b��e�b��R���b
 
 	 c o n s t   d o u b l e   R e c e i v e B a l l A n g l e   =   U t i l s : : N o r m a l i z e ( ( s e l f 2 g o a l . d i r ( )   +   r e v e r s e _ B a l l V e l D i r )   /   2 . 0 ) ;   / / \��e�b��e�b��e�b��e�b�R��ur������e�b��e�b��e�b��e�b��e�b- ��e�bXT- ��e�b��R�Q�b��e�b��e�b���X��r�e�b��e�b�d��e�b��e�bA���e�b#Z���b��v����e�b��e�b��e�b��e�b�pg!S�bOO��e�b
 
 	 c o n s t   d o u b l e   L a r g e R e c e i v e B a l l A n g l e   =   U t i l s : : N o r m a l i z e ( s e l f 2 g o a l . d i r ( )   /   3 . 0   +   2   *   r e v e r s e _ B a l l V e l D i r   /   3 . 0 ) ;   / / ��e�b��e�b��e�b��e�b��e�b��z�x�b\��e�b��e�b��e�b��e�b�R��ur��e�b��e�b��c����e�b��e�b��e�b�e�%m=\!S�b�pg!S�bOO��e�b
 
 
 
 
 
 	 b o o l   i s C a n D i r e c t K i c k   =   f a l s e ; 
 
 	 / / ��e�b��e�b��e�bo`��e�b��e�b��e�b�l��e�b? ? 
 
 	 i f (   i s S e n s o r e d   ) { 	 
 
 	 	 i f (   d A n g l e M e D i r 2 F i n a l K i c k   <   P a r a m : : M a t h : : P I / 1 0   ) { 
 
 	 	 	 i s C a n D i r e c t K i c k   =   t r u e ; 
 
 	 	 } 
 
 	 } 
 
 	 / / �V��e�b��e�bo`��e�b��e�b��e�b
 
 	 d o u b l e   g o _ k i c k _ f a c t o r   =   s e l f 2 r a w b a l l . m o d ( )   /   G O _ K I C K _ B A L L _ C R I T I C A L _ D I S T ; 	 
 
 	 g o _ k i c k _ f a c t o r   =   g o _ k i c k _ f a c t o r   >   1 . 0 ?   1 . 0   :   g o _ k i c k _ f a c t o r ; 	 / / �҉�^!S�b��e�b, ��e�b��e�b
 
 	 g o _ k i c k _ f a c t o r   =   g o _ k i c k _ f a c t o r   <   0 . 5 ?   0 . 5   :   g o _ k i c k _ f a c t o r ; 	 / / �҉�^!S�b��e�b, ��e�b��e�b
 
 	 d o u b l e   D i r e c t K i c k A l l o w A n g l e   =   g o _ k i c k _ f a c t o r * P a r a m : : V e h i c l e : : V 2 : : K I C K _ A N G L E ; 
 
 	 i f (   ! i s B a l l S p e e d F a s t   ) { 	 	 / / ��e�b��e�b��RO��b��e�b��e�b�S�Y��e�b��e�bo`
 
 	 	 i f (   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - m e . D i r ( ) ) )   <   / * 1 . 5 * * / D i r e c t K i c k A l l o w A n g l e 
 
 	 	 	 & &   d A n g l e M e D i r 2 F i n a l K i c k   <   P a r a m : : M a t h : : P I / 2 0   ) { 	 	 / / ��e�b��e�b��e�b��e�bMR��e�b  ��e�b    \��e�b��zy{�b��e�b�v��u�e��e�b
 
 	 	 	 	 i s C a n D i r e c t K i c k   =   t r u e ; 	 
 
 	 	 } 
 
 	 	 i f (   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   m e . D i r ( ) ) )   <   / * 1 . 5 * * / D i r e c t K i c k A l l o w A n g l e 
 
 	 	 	 & &   d A n g l e M e D i r 2 F i n a l K i c k   <   P a r a m : : M a t h : : P I / 2 0 
 
 	 	 	 & &   d A n g l e M e B a l l 2 B a l l V e l D i r   <   P a r a m : : M a t h : : P I / 4   
 
 	 	 	 | |   d A n g l e M e B a l l 2 B a l l V e l D i r   >   3 * P a r a m : : M a t h : : P I / 4   ) { 	 	 / / ��e�b��R�Q�b��e�b�b�S��e�b��e�b  ��e�b  �v��e�b��e�b��e�b��e�b  ��e�b N��e�b
 
 	 	 	 	 i s C a n D i r e c t K i c k   =   t r u e ; 
 
 	 	 } 
 
 	 	 i f (   b a l l S p e e d   <   5 0   & &   d i s t 2 b a l l   <   2 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   
 
 	 	 	 & &   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - m e . D i r ( ) ) )   <   P a r a m : : M a t h : : P I / 4 . 0   ) { 
 
 	 	 	 	 i s C a n D i r e c t K i c k   =   t r u e ; 
 
 	 	 } 
 
 	 } e l s e { 	 	 	 	 	 	 / /   ��e�b��e�b2O��e�b��e�b��v���Y��e�b��e�bo`
 
 	 	 i f (   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - m e . D i r ( ) ) )   < / *   1 . 2 5 * * / D i r e c t K i c k A l l o w A n g l e 
 
 	 	 	 & &   d A n g l e M e D i r 2 F i n a l K i c k   <   P a r a m : : M a t h : : P I / 3 0 
 
 	 	 	 & &   s e l f 2 r a w b a l l . m o d ( )   < =   G O _ K I C K _ B A L L _ C R I T I C A L _ D I S T   ) { 	 / / ��e�b��e�b��e�b��e�bMR��e�b  ��e�b    \��e�b��zy{�b��e�b�v��u�e��e�b
 
 	 	 	 	 i s C a n D i r e c t K i c k   =   t r u e ; 	 
 
 	 	 } 
 
 	 	 i f (   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   m e . D i r ( ) ) )   < / *   1 . 2 5 * * / D i r e c t K i c k A l l o w A n g l e 
 
 	 	 	 & &   d A n g l e M e D i r 2 F i n a l K i c k   <   P a r a m : : M a t h : : P I / 2 0 
 
 	 	 	 & &   d A n g l e M e B a l l 2 B a l l V e l D i r   <   P a r a m : : M a t h : : P I / 6   
 
 	 	 	 | |   d A n g l e M e B a l l 2 B a l l V e l D i r   >   5 * P a r a m : : M a t h : : P I / 6   ) { 	 	 / / ��e�b��R�Q�b��e�b�b�S��e�b��e�b  ��e�b  �v��e�b��e�b��e�b��e�b  ��e�b N��e�b
 
 	 	 	 	 i s C a n D i r e c t K i c k   =   t r u e ; 
 
 	 	 } 
 
 	 } 
 
 	 / /   ��e�bT o u c h K i c k P o s ��rxv�b��e�b��OO��bc l i f f y i n 
 
 	 d o u b l e   d A n g l e F o r K i c k D i r   =   f a b s ( U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r - s e l f 2 b a l l . d i r ( ) ) ) ; 
 
 	 d o u b l e   e x t r a _ b u f f e r   =   0 . 0 ; 
 
 	 b o o l   i s _ b a l l _ j u s t _ f r o n t   =   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - m e . D i r ( ) ) )   <   P a r a m : : V e h i c l e : : V 2 : : K I C K _ A N G L E 
 
 	 	 & &   s e l f 2 r a w b a l l . m o d ( )   <   2 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E ; 
 
 	 i f   ( i s _ b a l l _ j u s t _ f r o n t )   { 
 
 	 	 e x t r a _ b u f f e r   =   -   P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R * c o s ( d A n g l e F o r K i c k D i r ) * s e l f 2 b a l l . m o d ( ) / ( 1 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E )   -   2 ; 
 
 	 }   e l s e   { 
 
 	 	 e x t r a _ b u f f e r   =   m a x ( 5 . 0   -   2 * c o s ( d A n g l e F o r K i c k D i r ) , 3 . 5 ) ; 
 
 	 	 e x t r a _ b u f f e r   =   m i n ( e x t r a _ b u f f e r , 1 . 5 ) ; 
 
 	 } 
 
 
 
 	 / / c o u t < < " a a a a a a a a a :   " < <   f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) - m e . D i r ( ) ) ) < < "   " < <   s e l f 2 r a w b a l l . m o d ( ) < < "   " < < i s _ b a l l _ j u s t _ f r o n t < < e n d l ; 
 
 	 i s C a n D i r e c t K i c k   =   i s C a n D i r e c t K i c k   | |   i s _ b a l l _ j u s t _ f r o n t ; 
 
 	 i s B a l l I n F r o n t   =   i s B a l l I n F r o n t   | |   i s _ b a l l _ j u s t _ f r o n t ; 
 
 
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 / / 3 . C o n d i t i o n s   d e f i n i t i o n 
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 b o o l   a l l o w _ f o l l o w   =   d i s t 2 b a l l   <   F O L L O W B A L L _ C R I T I C A L _ D I S T ; 	 
 
 	 b o o l   a l l o w _ g o k i c k   =   i s C a n D i r e c t K i c k ; 
 
 	 b o o l   n e e d _ r u s h   =   d i s t 2 b a l l   >   F O L L O W B A L L _ C R I T I C A L _ D I S T   +   3 0 ; 
 
 	 b o o l   n e e d _ f o l l o w   =   d i s t 2 b a l l   >   G O _ K I C K _ B A L L _ C R I T I C A L _ D I S T   +   1 5 	 | |     f a b s ( U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   -   m e . D i r ( ) ) )   >   P a r a m : : M a t h : : P I / 2 . 0 / * 2 * P a r a m : : V e h i c l e : : V 2 : : K I C K _ A N G L E * / ; 
 
 
 
 	 b o o l   a l l o w _ w a i t   =   f a l s e ; 
 
 	 b o o l   n o t _ a l l o w _ w a i t   =   ! a l l o w _ w a i t ; 
 
 	 b o o l   a l l o w _ t o u c h _ s h o o t   =   ( f a b s ( d A n g D i f f R a w )   < =   P a r a m : : M a t h : : P I / 6 . 0 ) 
 
 	 	 	 	 	 	 	 	 & &   ( f a b s ( U t i l s : : N o r m a l i z e ( b a l l V e l D i r   -   U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) + P a r a m : : M a t h : : P I ) ) )   <   P a r a m : : M a t h : : P I / 2 . 5 ) 
 
 	 	 	 	 	 	 	 	 & &   ( b a l l S p e e d   >   2 5 ) ; 
 
 
 
 	 / / b o o l   a l l o w _ d r i f t _ s h o o t   =   f a b s ( b a l l V e l D i r ) < P a r a m : : M a t h : : P I * 1 0 0 / 1 8 0   & &   f a b s ( b a l l V e l D i r ) > P a r a m : : M a t h : : P I * 8 0 / 1 8 0 ; 
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 / / 4 . ��e�b��e�b�r`��e�b�~��e�b
 
 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 i f   ( b a l l S p e e d > = B a l l _ M o v i n g _ F a s t _ S p e e d ) 
 
 	 { 
 
 	 	 i n t   n e w _ s t a t e   =   s t a t e ( ) ; 
 
 	 	 i n t   o l d _ s t a t e ; 
 
 	 	 d o { 
 
 	 	 	 o l d _ s t a t e   =   n e w _ s t a t e ; 
 
 	 	 	 / / s t d : : c o u t   < <   " S t a t e : "   < <   o l d _ s t a t e   < <   " . \ n " ; 
 
 	 	 	 s w i t c h   ( o l d _ s t a t e )   { 
 
 	 	 	 c a s e   B E G I N N I N G : 	 	 	 / /   �v��e�b��e�b��e�b  G O T O 
 
 	 	 	 	 n e w _ s t a t e   =   R U S H _ T O _ B A L L ; 
 
 	 	 	 	 b r e a k ; 
 
 	 	 	 c a s e   R U S H _ T O _ B A L L : 	 	 	 
 
 	 	 	 	 i f   ( a l l o w _ f o l l o w )   { 
 
 	 	 	 	 	 n e w _ s t a t e   =   F O L L O W _ B A L L ; 
 
 	 	 	 	 } 
 
 	 	 	 	 i f   ( a l l o w _ w a i t ) { 
 
 	 	 	 	 	 n e w _ s t a t e = W A I T _ B A L L ; 
 
 	 	 	 	 } 
 
 	 	 	 	 b r e a k ; 
 
 	 	 	 c a s e   W A I T _ B A L L : 	 	 	 
 
 	 	 	 	 i f   ( n o t _ a l l o w _ w a i t ) 
 
 	 	 	 	 	 n e w _ s t a t e   =   F O L L O W _ B A L L ; 
 
 	 	 	 	 b r e a k ; 
 
 	 	 	 c a s e   F O L L O W _ B A L L : 
 
 	 	 	 	 i f   ( a l l o w _ g o k i c k )   { 
 
 	 	 	 	 	 	 n e w _ s t a t e   =   G O _ K I C K _ B A L L ; 
 
 	 	 	 	 } 
 
 	 	 	 	 i f   ( n e e d _ r u s h ) { 
 
 	 	 	 	 	 n e w _ s t a t e = R U S H _ T O _ B A L L ; 
 
 	 	 	 	 } 
 
 	 	 	 	 b r e a k ; 
 
 	 	 	 c a s e   G O _ K I C K _ B A L L : 
 
 	 	 	 	 i f   ( n e e d _ f o l l o w ) { 
 
 	 	 	 	 	 n e w _ s t a t e = F O L L O W _ B A L L ; 
 
 	 	 	 	 } 
 
 	 	 	 d e f a u l t : 
 
 	 	 	 	 n e w _ s t a t e   =   R U S H _ T O _ B A L L ; 
 
 	 	 	 	 b r e a k ; 
 
 	 	 	 } 
 
 	 	 }   w h i l e   ( f a l s e ) ; 
 
 	 	 s e t S t a t e ( n e w _ s t a t e ) ; 
 
 	 	 / / ��e�bU_��e�bMR��e�b��e�b
 
 	 	 _ l a s t C y c l e   =   p V i s i o n - > C y c l e ( ) ; 
 
 	 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 	 / / 5 . ��e�b�wc�x�bMR��e�bo`�ThT�d�b��e�b��e�b��v�0�b��O�b���:   ��e�b��e�b����e�b��e�b��e�b��e�b��e�b��e�b��\��e�b����e�b��e�b�^��e�bKN��\/ / ��e�b����e�bMO��wwx�b��e�b��e�b��e�b
 
 	 	 / /   T O D O ��e�bT O D O     T O D O 
 
 	 	 / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / 
 
 	 	 d o u b l e   p r e d i c t _ f a c t o r   =   1 . 0 ; 	 / / ��e�bMO��e�b����e�b��e�b��e�b
 
 	 	 d o u b l e   b a l l V e l _ f a c t o r   =   1 . 0 ; 	 / / ��e�b��e�bq_��e�b��e�b��e�b
 
 	 	 c o n s t   C V e c t o r   r a w B a l l 2 p r e d i c t B a l l   =   p r e d i c t _ p o s B a l l   -   b a l l . P o s ( ) ; 
 
 	 	 i f (   m e O n B a l l M o v i n g S e g   ) { 	 / / \��e�b�bq_��e�b��e�b��e�b��r���b��e�b��e�b������e�b��e�b��e�b��z�d�b��e�b��e�b��e�bMR
 
 	 	 	 p r e d i c t _ f a c t o r   =   s q r t ( s e l f 2 r a w b a l l . m o d ( ) / 1 5 0 ) * s q r t ( s q r t ( b a l l S p e e d / 2 5 0 ) ) ; 
 
 	 	 	 p r e d i c t _ f a c t o r   * =   s q r t ( d S p e e d M e 2 B a l l / 1 0 0 ) ; 
 
 
 
 	 	 }   e l s e   { 
 
 	 	 	 p r e d i c t _ f a c t o r   =   s q r t ( b a l l S p e e d / 2 5 0 ) * s q r t ( s q r t ( s e l f 2 r a w b a l l . m o d ( ) / 1 5 0 ) ) ; 
 
 	 	 	 p r e d i c t _ f a c t o r   * =   s q r t ( d S p e e d M e 2 B a l l / 1 5 0 ) ; 
 
 	 	 } 
 
 	 	 i f (   b a l l S p e e d   <   5 0   ) { 
 
 	 	 	 p r e d i c t _ f a c t o r   + =   0 . 5 ; 
 
 	 	 	 p r e d i c t _ f a c t o r   =   p r e d i c t _ f a c t o r > 1 . 2 5 ? 1 . 2 5 : p r e d i c t _ f a c t o r ; 
 
 	 	 }   e l s e   { 
 
 	 	 	 p r e d i c t _ f a c t o r   - =   0 . 2 5 ; 
 
 	 	 	 p r e d i c t _ f a c t o r   =   p r e d i c t _ f a c t o r > 0 . 7 5 ? 0 . 7 5 : p r e d i c t _ f a c t o r ; 
 
 	 	 	 p r e d i c t _ f a c t o r   =   p r e d i c t _ f a c t o r < 0 . 2 5 ? 0 . 2 5 : p r e d i c t _ f a c t o r ; 
 
 	 	 } 
 
 	 	 C V e c t o r   e x t r a _ b a l l _ v e l   =   r a w B a l l 2 p r e d i c t B a l l   *   p r e d i c t _ f a c t o r ; 
 
 	 	 / / / / / / / / / / / / / / / / / / / ? ? 
 
 	 	 i f   ( f a b s ( U t i l s : : N o r m a l i z e ( e x t r a _ b a l l _ v e l . d i r ( ) - b a l l . V e l ( ) . d i r ( ) ) )   >   P a r a m : : M a t h : : P I / 3 . 0 )   { 
 
 	 	 	 e x t r a _ b a l l _ v e l   =   e x t r a _ b a l l _ v e l   *   ( - 1 . 0 ) ; 
 
 	 	 } 
 
 
 
 	 	 C G e o P o i n t   r e a l _ p r e d i c t _ b a l l P o s   =   b a l l . P o s ( )   +   e x t r a _ b a l l _ v e l ; 
 
 
 
 	 	 / / s o m e   t e m p t   v a r i a b l e s 
 
 	 	 C G e o P o i n t   p r o j _ t e m p ; 
 
 	 	 C V e c t o r   t m p ; 
 
 	 	 d o u b l e   g o k i c k F a c t o r   =   1 . 0 ; 
 
 	 	 d o u b l e   m y V e l S p e e d R e l a t i v e 2 F i n a l   =   m e . V e l ( ) . m o d ( ) * c o s ( U t i l s : : N o r m a l i z e ( m e . V e l ( ) . d i r ( ) - f i n a l K i c k D i r ) ) ; 
 
 	 	 T a s k T   c h a s e _ k i c k _ t a s k ( t a s k ( ) ) ; 
 
 	 	 s w i t c h (   s t a t e ( )   ) 
 
 	 	 { 
 
 	 	 c a s e   R U S H _ T O _ B A L L : 
 
 	 	 	 / / c o u t < < " R U S H _ T O _ B A L L " < < e n d l ; 
 
 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( r e a l _ p r e d i c t _ b a l l P o s , " R U S H _ T O _ B A L L " ) ; 
 
 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ x ( r e a l _ p r e d i c t _ b a l l P o s , C O L O R _ C Y A N ) ; 
 
 	 	 	 i f   ( ! m e O n B a l l M o v i n g L o n g S e g )   {                                                               / / ��e�b��e�b�bq_��e�b��e�b��e�b��e�b��r���b��e�b���O��b����e�b%�MO��e�b��e�b��e�b܏
 
 	 	 	 	 i f   ( f a b s ( d A n g D i f f R a w )   < =   P a r a m : : M a t h : : P I   /   2 . 0 )   { 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( 1 . 5   *   P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E ,   r e v e r s e _ f i n a l D i r ) ; 
 
 	 	 	 	 	 / / a d d   f r o n t   v e l 
 
 	 	 	 	 	 i f   ( i s B a l l T o G o a l )   { 
 
 	 	 	 	 	 	 i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l   <   5 0 )   { 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l     +   U t i l s : : P o l a r 2 V e c t o r ( 5 0 ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l   <   7 5 )   { 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l     +   U t i l s : : P o l a r 2 V e c t o r ( 3 0   +   m y V e l S p e e d R e l a t i v e 2 F i n a l ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l   +   U t i l s : : P o l a r 2 V e c t o r ( 2 5   +   m y V e l S p e e d R e l a t i v e 2 F i n a l ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l   <   5 0 )   { 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 5 0 ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l   <   7 5 )   { 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 3 0   +   m y V e l S p e e d R e l a t i v e 2 F i n a l ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 2 5   +   m y V e l S p e e d R e l a t i v e 2 F i n a l ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 i f   ( c h a s e _ k i c k _ t a s k . p l a y e r . v e l . m o d ( )   >   s p e e d _ f a c t o r   *   M a x S p e e d )   { 	 / / ��e�b��e�b
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l   *   ( s p e e d _ f a c t o r   *   M a x S p e e d   /   c h a s e _ k i c k _ t a s k . p l a y e r . v e l . m o d ( ) ) ; 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   c h a s e _ k i c k _ t a s k . p l a y e r . v e l ; 
 
 	 	 	 	 	 } 
 
 	 	 	 	 } 
 
 	 	 	 	 e l s e   { 	 / / ��e�b�҉�a�b��e�b
 
 	 	 	 	 	 d o u b l e   n o w d i r   =   U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   +   P a r a m : : M a t h : : P I ) ; 
 
 	 	 	 	 	 i n t   s i g n   =   U t i l s : : N o r m a l i z e ( ( n o w d i r   -   f i n a l K i c k D i r ) ) > 0   ?   1   :   - 1 ; 
 
 	 	 	 	 	 n o w d i r   =   U t i l s : : N o r m a l i z e ( n o w d i r   +   s i g n * P a r a m : : M a t h : : P I   /   2 . 0 ) ; 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   b a l l . P o s ( )   +   U t i l s : : P o l a r 2 V e c t o r ( 1 . 5 * P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E ,   n o w d i r ) ; 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   C V e c t o r ( 0 ,   0 ) ; 
 
 	 	 	 	 } 
 
 	 	 	 } 
 
 	 	 	 e l s e   {             / / ��e�b��e�b��e�b���
 
 	 	 	 	 i f   ( i s B a l l A t F r o n t )   {                 / / ��e�b���y{�bMR
 
                                         i f   ( r e a l _ p r e d i c t _ b a l l P o s . x ( )   >   P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2   -     1 . 5   *   P a r a m : : F i e l d : : P E N A L T Y _ A R E A _ D E P T H   )   { 
 
 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / / ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,     f r o n t   f i e l d ,   r e c e i v e   b a l l   i n   h i g h   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   {                                           / / ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,     f r o n t   f i e l d ,   r e c e i v e   b a l l   i n   l o w   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 i f   ( i s B a l l A t D i r e c t F r o n t )   { 
 
 	 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / / ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,   l a r g e   r e c e i v e   b a l l   i n   h i g h   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   L a r g e R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   L a r g e R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 	 e l s e   {                                           / / ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,   l a r g e   r e c e i v e   b a l l   i n   l o w   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   L a r g e R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   L a r g e R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / / ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,   r e c e i v e   b a l l   i n   h i g h   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 	 e l s e   {                                           / / ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,   r e c e i v e   b a l l   i n   l o w   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 } 
 
 	 	 	 	 e l s e   {                                     / / ��e�b f��e�b���y{�b��e�b
 
 	 	 	 	 	 i f   (   i s B a l l T o G o a l )   { 
 
 	 	 	 	 	 	 	 	 	 	 / / ��e�b��e�b��!S�b�V��e�b�S��e�b��e�b�%m�Q4s�b��e�bx ��~�e��e�b�R���b, �pg!S�b��e�bTKNMR�pg!S�b��e�b��e�b��e�b��e�b
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 , 3 6 1 ) ,   " B a l l   f r o m   b e h i n d ,   d o d g e   b a l l " ) ; 
 
 	 	 	 	 	 	 d o u b l e   n o w d i r   =   U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   +   P a r a m : : M a t h : : P I ) ; 
 
 	 	 	 	 	 	 i n t   s i g n   =   U t i l s : : N o r m a l i z e ( ( n o w d i r   -   f i n a l K i c k D i r ) ) > 0   ?   1   :   - 1 ; 
 
 	 	 	 	 	 	 n o w d i r   =   U t i l s : : N o r m a l i z e ( n o w d i r   +   s i g n * P a r a m : : M a t h : : P I   /   2 . 0 ) ; 
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E ,   n o w d i r ) ; 
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   C V e c t o r ( 0 ,   0 ) ; 
 
 	 	 	 	 	 } 
 
                                         e l s e   i f   ( r e a l _ p r e d i c t _ b a l l P o s . x ( )   >   P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2   -   1 . 5   *   P a r a m : : F i e l d : : P E N A L T Y _ A R E A _ D E P T H )   { 
 
 	 	 	 	 	 	 / / ��e�b����ry{�bMR��e�b��e�b�S��e�b��e�b��e�b�S��e�b��e�b��e�bOO�%m���b����wy{�b��e�b
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 , 3 6 1 ) ,   " B a l l   f r o m   b e h i n d ,   f r o n t   f i e l d ,   r e c e i v e   b a l l " ) ; 
 
 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / / ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   {                                           / / ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 , 3 6 1 ) ,   " B a l l   f r o m   b e h i n d ,   r e c e i v e   b a l l " ) ; 
 
 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / / ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   {                                           / / ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 } 
 
 	 	 	 } 
 
 
 
 	 	 	 b r e a k ; 
 
 
 
 	 	 c a s e   W A I T _ B A L L : 
 
 	 	 	 / / c o u t < < " W A I T _ B A L L " < < e n d l ; 
 
 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( r e a l _ p r e d i c t _ b a l l P o s ,   " W A I T _ B A L L " ) ; 
 
 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   s e l f 2 t a r g e t L i n e _ b a l l M o v i n g L i n e _ s e c P o s 
 
 	 	 	 	 +   U t i l s : : P o l a r 2 V e c t o r ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E + P a r a m : : F i e l d : : B A L L _ S I Z E , U t i l s : : N o r m a l i z e ( r e v e r s e _ f i n a l D i r ) ) ; 
 
 	 	 	 p r o j _ t e m p   =   b a l l M o v i n g S e g . p r o j e c t i o n ( c h a s e _ k i c k _ t a s k . p l a y e r . p o s ) ; 
 
 	 	 	 f o r ( i n t   i   =   0 ;   i   <   1 0 ;   i + + ) { 
 
 	 	 	 	 i f (   p r o j _ t e m p . d i s t ( c h a s e _ k i c k _ t a s k . p l a y e r . p o s )   < =   1 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E + P a r a m : : F i e l d : : B A L L _ S I Z E + 3   ) { 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   c h a s e _ k i c k _ t a s k . p l a y e r . p o s   
 
 	 	 	 	 	 	 +   U t i l s : : P o l a r 2 V e c t o r ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E + P a r a m : : F i e l d : : B A L L _ S I Z E , U t i l s : : N o r m a l i z e ( r e v e r s e _ f i n a l D i r ) ) ; 
 
 	 	 	 	 	 p r o j _ t e m p   =   b a l l M o v i n g S e g . p r o j e c t i o n ( c h a s e _ k i c k _ t a s k . p l a y e r . p o s ) ; 
 
 	 	 	 	 } 
 
 	 	 	 	 b r e a k ; 
 
 	 	 	 } 
 
 
 
 	 	 	 b r e a k ; 
 
 
 
 	 	 c a s e   F O L L O W _ B A L L : 	 
 
 	 	 	 / / c o u t < < " F O L L O W _ B A L L " < < e n d l ; 
 
 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( b a l l . P o s ( ) , " F O L L O W _ B A L L " ) ; 
 
 	 	 	 i f   ( ! m e O n B a l l M o v i n g L o n g S e g )   {                               / /   ����e�b
 
 	 	 	 	 p r o j D i s t   =   ( p r o j D i s t   <   P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E   +   5 )   ? 
 
 	 	 	 	 	 P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E   +   5   :   p r o j D i s t   -   3 ; 
 
 	 	 	 	 p r o j D i s t   =   ( p r o j D i s t   >   1 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E )   ? 
 
 	 	 	 	 	 1 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E   :   p r o j D i s t   -   2 ; 
 
 	 	 	 	 i f   ( ! i s B a l l I n F r o n t   & &   b a l l S p e e d   < =   5 0 )   { 
 
 	 	 	 	 	 p r o j D i s t   =   1 . 5 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E ; 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   b a l l . P o s ( )   +   U t i l s : : P o l a r 2 V e c t o r ( p r o j D i s t ,   r e v e r s e _ f i n a l D i r ) ; 
 
 	 	 	 	 } 
 
 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( p r o j D i s t ,   r e v e r s e _ f i n a l D i r ) ; 
 
 	 	 	 	 } 
 
 
 
 	 	 	 	 i f   ( b a l l . V e l ( ) . m o d ( )   <   3 0 )   { 	 / /   ��e�b��Rxv�b\��e�b��e�b��e�b��e�b��e�b��RO��b��e�b��e�b��e�b��e�b��e�b��e�b��e�b��e�b���
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   b a l l . V e l ( )   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 5 0 ,   f i n a l K i c k D i r ) ; 
 
 	 	 	 	 } 
 
 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 b a l l V e l _ f a c t o r   =   s q r t ( b a l l 2 p r o j D i s t   /   ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   +   P a r a m : : F i e l d : : B A L L _ S I Z E ) ) ; 
 
 	 	 	 	 	 b a l l V e l _ f a c t o r   =   b a l l V e l _ f a c t o r   >   1 . 2 5   ?   1 . 2 5   :   b a l l V e l _ f a c t o r ; 
 
 	 	 	 	 	 i f   ( b a l l M o v i n g S e g . I s P o i n t O n L i n e O n S e g m e n t ( p r o j M e ) )   { 	 	 / /   \��e�b��z�d�b����e�b��e�b
 
 	 	 	 	 	 	 b a l l V e l _ f a c t o r   * =   - 0 . 5 ; 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 	 / /   ��e�b��e�b��e�b��e�b  &   ��e�bMR��R���b
 
 	 	 	 	 	 	 b a l l V e l _ f a c t o r   * =   0 . 7 5 ; 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 t m p   =   b a l l . V e l ( ) * b a l l V e l _ f a c t o r ; 
 
 	 	 	 	 	 i f   ( i s B a l l T o G o a l )   { 
 
 	 	 	 	 	 	 i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l   <   1 5 )   { 
 
 	 	 	 	 	 	 	 t m p   =   t m p     +   U t i l s : : P o l a r 2 V e c t o r ( 1 5 ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l < 3 0 )   { 
 
 	 	 	 	 	 	 	 t m p   =   t m p   +   U t i l s : : P o l a r 2 V e c t o r ( 1 5   +   m y V e l S p e e d R e l a t i v e 2 F i n a l ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 	 t m p   =   t m p   +   U t i l s : : P o l a r 2 V e c t o r ( 3 0 ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l   <   1 5 )   { 
 
 	 	 	 	 	 	 	 t m p   =   t m p   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 2 0 ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   i f   ( m y V e l S p e e d R e l a t i v e 2 F i n a l < 3 0 )   { 
 
 	 	 	 	 	 	 	 t m p   =   t m p   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 4 0   +   m y V e l S p e e d R e l a t i v e 2 F i n a l ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 	 t m p   =   t m p   *   1 . 5   +   U t i l s : : P o l a r 2 V e c t o r ( 5 0 ,   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 i f   ( t m p . m o d ( )   >   s p e e d _ f a c t o r   *   M a x S p e e d )   { 	 / /   ��e�b��e�b
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   t m p   *   ( s p e e d _ f a c t o r   *   M a x S p e e d   /   t m p . m o d ( ) ) ; 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   t m p ; 
 
 	 	 	 	 	 } 
 
 	 	 	 	 } 
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . n e e d d r i b b l e   =   t r u e ; 
 
 	 	 	 } 
 
 	 	 	 e l s e   {             / /   ��e�b��e�b��e�b���
 
 	 	 	 	 i f   ( i s B a l l A t F r o n t )   {                 / /   ��e�b���y{�bMR
 
                                         i f   ( r e a l _ p r e d i c t _ b a l l P o s . x ( )   >   P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2   -   1 . 5   *   P a r a m : : F i e l d : : P E N A L T Y _ A R E A _ D E P T H   )   { 
 
 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / /   ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,     f r o n t   f i e l d ,   r e c e i v e   b a l l   i n   h i g h   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   {                                           / /   ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 i f   ( i s B a l l A t D i r e c t F r o n t )   {   
 
 	 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / /   ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,   l a r g e   r e c e i v e   b a l l   i n   h i g h   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   L a r g e R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   L a r g e R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 	 e l s e   {                                           / /   ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   L a r g e R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   L a r g e R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / /   ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 ,   3 6 1 ) ,   " N E E D _ T U R N ,   r e c e i v e   b a l l   i n   h i g h   s p e e d " ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 	 e l s e   {                                           / /   ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 } 
 
 	 	 	 	 e l s e   {                                     / / ��e�b f��e�b���y{�b��e�b
 
 	 	 	 	 	 i f   ( i s B a l l T o G o a l )   { 
 
 	 	 	 	 	 	 / /   ��e�b��e�b��!S�b�V��e�b�S��e�b��e�b�%m�Q4s�b��e�bx ��~�e��e�b�R���b, �pg!S�b��e�bTKNMR�pg!S�b��e�b��e�b��e�b��e�b
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 , 3 6 1 ) ,   " B a l l   f r o m   b e h i n d ,   d o d g e   b a l l " ) ; 
 
 	 	 	 	 	 	 d o u b l e   n o w d i r   =   U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( )   +   P a r a m : : M a t h : : P I ) ; 
 
 	 	 	 	 	 	 i n t   s i g n   =   U t i l s : : N o r m a l i z e ( ( n o w d i r   -   f i n a l K i c k D i r ) ) > 0   ?   1   :   - 1 ; 
 
 	 	 	 	 	 	 n o w d i r   =   U t i l s : : N o r m a l i z e ( n o w d i r   +   s i g n * P a r a m : : M a t h : : P I   /   2 . 0 ) ; 
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( 1 . 5   *   P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E ,   n o w d i r ) ; 
 
 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   C V e c t o r ( 0 ,   0 ) ; 
 
 	 	 	 	 	 } 
 
                                         e l s e   i f   ( r e a l _ p r e d i c t _ b a l l P o s . x ( )   >   P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2   -   1 . 5   *   P a r a m : : F i e l d : : P E N A L T Y _ A R E A _ D E P T H )   { 
 
 	 	 	 	 	 	 / /   ��e�b����ry{�bMR��e�b��e�b�S��e�b��e�b��e�b�S��e�b��e�b��e�bOO�%m���b����wy{�b��e�b
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 , 3 6 1 ) ,   " B a l l   f r o m   b e h i n d ,   f r o n t   f i e l d ,   r e c e i v e   b a l l " ) ; 
 
 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / /   ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   {                                           / /   ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   r e v e r s e _ B a l l V e l D i r ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   r e v e r s e _ B a l l V e l D i r ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 	 e l s e   { 
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 2 5 1 , 3 6 1 ) ,   " B a l l   f r o m   b e h i n d ,   r e c e i v e   b a l l " ) ; 
 
 	 	 	 	 	 	 i f   ( b a l l S p e e d   >   5 0 )   {               / /   ��e�b��R��!S�b, �z��e�b��e�b��e�b�bq_��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   p r o j M e   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 	 e l s e   {                                           / /   ��e�b��R�e�b��e�b��e�b�z\��e�b����e�bMO��e�b
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( - P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R ,   R e c e i v e B a l l A n g l e ) ; 
 
 	 	 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   R e c e i v e B a l l A n g l e ; 
 
 	 	 	 	 	 	 } 
 
 	 	 	 	 	 } 
 
 	 	 	 	 } 
 
 	 	 	 } 
 
 	 	 	 b r e a k ; 
 
 
 
 	 	 c a s e   G O _ K I C K _ B A L L : 
 
 	 	 	 / /   c o u t < < " G O _ K I C K _ B A L L " < < e n d l ; 
 
 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( b a l l . P o s ( ) ,   " G O _ K I C K _ B A L L " ) ; 
 
 	 	 	 g o k i c k F a c t o r   =   ( d A n g l e M e B a l l 2 M e D i r / P a r a m : : V e h i c l e : : V 2 : : K I C K _ A N G L E )   *   d i s t 2 b a l l / ( 2 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E + P a r a m : : F i e l d : : B A L L _ S I Z E ) ; 
 
 	 	 	 i f (   g o k i c k F a c t o r   >   1 . 2 5   ) { 
 
 	 	 	 	 g o k i c k F a c t o r   =   1 . 2 5 ; 
 
 	 	 	 }   e l s e   i f (   g o k i c k F a c t o r   <   0 . 7 5   ) { 
 
 	 	 	 	 i f   ( m e O n B a l l M o v i n g S e g )   { 
 
 	 	 	 	 	 g o k i c k F a c t o r   =   0 . 5 ; 
 
 	 	 	 	 } e l s e { 
 
 	 	 	 	 	 g o k i c k F a c t o r   =   0 . 7 5 ; 
 
 	 	 	 	 } 
 
 	 	 	 } 
 
 	 	 	 i f (   ! i s B a l l I n F r o n t   ) { 
 
 	 	 	 	 g o k i c k F a c t o r   =   1 . 5 ; 
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   b a l l . P o s ( )   +   U t i l s : : P o l a r 2 V e c t o r ( g o k i c k F a c t o r * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R , r e v e r s e _ f i n a l D i r ) ; 
 
 	 	 	 } e l s e { 
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s 
 
 	 	 	 	 	 +   U t i l s : : P o l a r 2 V e c t o r ( g o k i c k F a c t o r * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ F R O N T _ T O _ C E N T E R , r e v e r s e _ f i n a l D i r ) ; 
 
 	 	 	 } 
 
 
 
 	 	 	 b a l l V e l _ f a c t o r   =   s q r t ( b a l l 2 p r o j D i s t / ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E + P a r a m : : F i e l d : : B A L L _ S I Z E ) ) * s q r t ( b a l l S p e e d / 1 0 0 ) ; 
 
 	 	 	 b a l l V e l _ f a c t o r   =   b a l l V e l _ f a c t o r   >   1 . 0 ? 1 . 0 : b a l l V e l _ f a c t o r ; 
 
 	 	 	 i f (   b a l l M o v i n g S e g . I s P o i n t O n L i n e O n S e g m e n t ( p r o j M e )   ) { 	 	 / /   \��e�b��z�d�b����e�b��e�b
 
 	 	 	 	 b a l l V e l _ f a c t o r   * =   - 0 . 5 ; 
 
 	 	 	 } e l s e { 	 / /   ��e�b��e�b��e�b��e�b  &   ��e�bMR��R���b
 
 	 	 	 	 i f (   i s B a l l I n F r o n t   ) 
 
 	 	 	 	 	 b a l l V e l _ f a c t o r   * =   0 . 7 5 ; 	 
 
 	 	 	 	 e l s e 
 
 	 	 	 	 	 b a l l V e l _ f a c t o r   * =   1 . 2 5 ; 	 
 
 
 
 	 	 	 } 
 
 	 	 	 t m p   =   b a l l . V e l ( ) * b a l l V e l _ f a c t o r ; 
 
 	 	 	 i f (   m y V e l S p e e d R e l a t i v e 2 F i n a l   <   2 5   )   { 
 
 	 	 	 	 t m p   =   t m p   +   U t i l s : : P o l a r 2 V e c t o r ( 2 5 , U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 }   e l s e   i f ( m y V e l S p e e d R e l a t i v e 2 F i n a l < 5 0 )   { 
 
 	 	 	 	 t m p   =   t m p   +   U t i l s : : P o l a r 2 V e c t o r ( 2 5 + m y V e l S p e e d R e l a t i v e 2 F i n a l , U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 }   e l s e   { 
 
 	 	 	 	 t m p   =   t m p   +   U t i l s : : P o l a r 2 V e c t o r ( 7 5 , U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ) ; 
 
 	 	 	 } 
 
 	 	 	 i f (   t m p . m o d ( )   >   s p e e d _ f a c t o r   *   M a x S p e e d   ) { 	 / /   ��e�b��e�b
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   t m p * ( s p e e d _ f a c t o r * M a x S p e e d / t m p . m o d ( ) ) ; 
 
 	 	 	 } e l s e { 
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   t m p ; 
 
 	 	 	 } 	 	 	 	 
 
 	 	 	 b r e a k ; 
 
 	 	 d e f a u l t   : 
 
 	 	 	 b r e a k ; 
 
 	 	 } 
 
 	 	 / /   ��e�b��e�b���
 
 	 	 i f (   s t a t e ( )   = =   F O L L O W _ B A L L   | |   s t a t e ( )   = =   G O _ K I C K _ B A L L ) { 
 
 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( b a l l . P o s ( ) ,   " F O L L O W _ B A L L   o r   G O _ K I C K _ B A L L " ) ; 
 
 	 	 	 i f (   m e O n B a l l M o v i n g S e g   & &   p r o j D i s t   <   2 * P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E   & &   b a l l S p e e d   >   5 0   & &   ( d A n g l e M e B a l l 2 B a l l V e l D i r   <   P a r a m : : M a t h : : P I / 4   | |   d A n g l e M e B a l l 2 B a l l V e l D i r   >   P a r a m : : M a t h : : P I * 3 / 4 ) ) { 
 
 	 	 	 	 i f (   f a b s ( U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r - b a l l V e l D i r ) )   <   P a r a m : : M a t h : : P I / 3 . 0   | |   f a b s ( U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r - b a l l V e l D i r ) )   >   P a r a m : : M a t h : : P I * 2 . 0 / 3 . 0   ) { 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   b a l l . P o s ( )   +   U t i l s : : P o l a r 2 V e c t o r ( 2 . 0 * P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E , U t i l s : : N o r m a l i z e ( ( m e . P o s ( ) - p r o j M e ) . d i r ( ) ) ) ; 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   C V e c t o r ( 0 . 0 , 0 . 0 ) ; 
 
 	 	 	 	 } e l s e { 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   b a l l . P o s ( )   +   U t i l s : : P o l a r 2 V e c t o r ( 1 . 5 * P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E , U t i l s : : N o r m a l i z e ( ( m e . P o s ( ) - p r o j M e ) . d i r ( ) )   ) ; 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   C V e c t o r ( 0 . 0 , 0 . 0 ) ; 
 
 	 	 	 	 } 	 	 
 
 
 
 	 	 	 	 i f (   d A n g l e M e B a l l 2 B a l l V e l D i r   <   P a r a m : : M a t h : : P I / 5   ) { 
 
 	 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   c h a s e _ k i c k _ t a s k . p l a y e r . p o s   +   U t i l s : : P o l a r 2 V e c t o r ( 2 . 0 * P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E , U t i l s : : N o r m a l i z e ( ( m e . P o s ( ) - p r o j M e ) . d i r ( ) )   ) ; 
 
 	 	 	 	 } 
 
 	 	 	 } 
 
 	 	 	 i f (   / * f a b s ( d A n g D i f f R a w )   > =   P a r a m : : M a t h : : P I / 3 . 0   & & * /   ! i s B a l l I n F r o n t   & &   d i s t 2 b a l l   <   P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E + 5 ) { 
 
 	 	 	 	 d o u b l e   n o w d i r   =   U t i l s : : N o r m a l i z e ( s e l f 2 r a w b a l l . d i r ( ) + P a r a m : : M a t h : : P I ) ; 
 
 	 	 	 	 i n t   s i g n   =   U t i l s : : N o r m a l i z e ( ( n o w d i r   -   f i n a l K i c k D i r ) ) > 0 ? 1 : - 1 ; 
 
 	 	 	 	 n o w d i r   =   U t i l s : : N o r m a l i z e ( n o w d i r + s i g n * P a r a m : : M a t h : : P I / 2 . 0 ) ; 
 
 
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . p o s   =   r e a l _ p r e d i c t _ b a l l P o s   +   U t i l s : : P o l a r 2 V e c t o r ( 5 . 0 * P a r a m : : F i e l d : : M A X _ P L A Y E R _ S I Z E , n o w d i r ) ; 
 
 	 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   C V e c t o r ( 0 , 0 ) ; 
 
 	 	 	 } 
 
 	 	 } 
 
 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . r o t v e l   =   0 . 0 ; 
 
 
 
 	 	 / * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * / 
 
 	 	 / *   6 . T o u c h   K i c k ��e�b��S�ewx�b��e�b��e�b��e�b��e�b	 	 	 	 	 	 	 	 	 	 	 * / 
 
 	 	 / * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * / 
 
 	 
 
 	 	 i f   ( a l l o w _ t o u c h _ s h o o t )   { 	 	 	 	 	 	 / / /   ��e�b�e��e�b��e�b��e�b��e�b��e�b��e�b��e�b��e�b
 
 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . i s p a s s   =   f a l s e ; 
 
 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e   =   U t i l s : : N o r m a l i z e ( f i n a l K i c k D i r ) ; 
 
 	 	 	 s e t S u b T a s k ( T a s k F a c t o r y V 2 : : I n s t a n c e ( ) - > T o u c h K i c k ( c h a s e _ k i c k _ t a s k ) ) ; 
 
 	 	 } 
 
 	 	 e l s e   i f   ( b a l l S p e e d   <   3 5 / *   & &   b a l l I n f r o n t * / )   { 	 	 / / /   ��e�b��e�b��e�b��e�b��e�b��e�b�O��S&�b��e�b��e�b��e�b���
 
 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . v e l   =   U t i l s : : P o l a r 2 V e c t o r ( 2 5 ,   t a s k ( ) . p l a y e r . a n g l e ) ; 
 
 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . a n g l e     =   t a s k ( ) . p l a y e r . a n g l e ; 
 
 	 	 	 c h a s e _ k i c k _ t a s k . p l a y e r . f l a g   =   p l a y e r F l a g ; 
 
 	 	 	 s e t S u b T a s k ( T a s k F a c t o r y V 2 : : I n s t a n c e ( ) - > N o n e T r a j G e t B a l l ( c h a s e _ k i c k _ t a s k ) ) ; 
 
 	 	 	 / / 	 s e t S u b T a s k ( T a s k F a c t o r y V 2 : : I n s t a n c e ( ) - > G e t B a l l V 4 ( c h a s e _ k i c k _ t a s k ) ) ; 
 
 	 	 }   
 
 	 	 e l s e   { 
 
 	 	 	 C V e c t o r   m i d d l e S e l f 2 b a l l   =   s e l f 2 b a l l * 0 . 5   +   ( b a l l . P o s ( ) - m e . P o s ( ) ) * 0 . 5 ; 
 
 	 	 	 d o u b l e   d A n g l e F r o n t   =   U t i l s : : N o r m a l i z e ( m i d d l e S e l f 2 b a l l . d i r ( ) - m e . D i r ( ) ) ; 
 
 	 	 	 i n t   s i g n F r o n t   =   d A n g l e F r o n t   >   0 . 0   ?   + 1 : - 1 ; 	 / /   + 1 / ��c�a�b  - 1 / ��e�b���
 
 	 	 	 i f   ( G O _ K I C K _ B A L L   = =   s t a t e ( ) )   { 
 
 	 	 	 	 / / f i x   m e 
 
 	 	 	 	 i f ( f a b s ( d A n g D i f f )   <   P a r a m : : M a t h : : P I / 3 6   & &   s e l f 2 b a l l . m o d ( )   <   P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E * 1 . 5 
 
 	 	 	 	 	 & &   b a l l . V e l ( ) . m o d ( )   <   3 5 )   { 
 
 	 	 	 	 	 	 d o u b l e   d i r e c t _ V x   =   5 0   *   s q r t ( s e l f 2 b a l l . m o d ( ) / ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E * 1 . 5 ) ) ; 
 
 	 	 	 	 	 	 d o u b l e   d i r e c t _ V y   =   - s i g n F r o n t   *   1 5   *   s q r t ( ( P a r a m : : V e h i c l e : : V 2 : : P L A Y E R _ S I Z E * 1 . 5 ) / ( s e l f 2 b a l l . m o d ( ) + 2 ) ) ; 
 
 	 	 	 	 	 	 c h a r   V x _ d e b u g M s g [ 1 0 0 ] ; 
 
 	 	 	 	 	 	 s p r i n t f ( V x _ d e b u g M s g ,   " % f " ,   d i r e c t _ V x ) ; 
 
 	 	 	 	 	 	 c h a r   V y _ d e b u g M s g [ 1 0 0 ] ; 
 
 	 	 	 	 	 	 s p r i n t f ( V y _ d e b u g M s g ,   " % f " ,   d i r e c t _ V y ) ; 
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 3 0 0 ,   3 0 0 ) ,   V x _ d e b u g M s g ,   C O L O R _ C Y A N ) ; 
 
 	 	 	 	 	 	 G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( C G e o P o i n t ( 3 0 0 ,   2 5 0 ) ,   V y _ d e b u g M s g ,   C O L O R _ C Y A N ) ; 
 
 	 	 	 	 	 	 / / /   < s u m m a r y > 
 
 	 	 	 	 	 	 / / /   ��e�b��e�b��e�b���
 
 	 	 	 	 	 	 / / /   < / s u m m a r y > 
 
 	 	 	 	 	 	 / / /   < p a r a m   n a m e = " p V i s i o n " > < / p a r a m > 
 
 	 	 	 	 	 	 _ d i r e c t C o m m a n d   =   C m d F a c t o r y : : I n s t a n c e ( ) - > n e w C o m m a n d ( C P l a y e r S p e e d V 2 ( r o b o t N u m ,   d i r e c t _ V x ,   d i r e c t _ V y ,   0 ,   0 ) ) ; 
 
 	 	 	 	 }   e l s e   { 
 
 	 	 	 	 	 s e t S u b T a s k ( T a s k F a c t o r y V 2 : : I n s t a n c e ( ) - > S m a r t G o t o P o s i t i o n ( c h a s e _ k i c k _ t a s k ) ) ; 
 
 	 	 	 	 } 
 
 
 
 	 	 	 	 i f   ( b a l l . P o s ( ) . x ( )   <   -   P a r a m : : F i e l d : : P I T C H _ L E N G T H / 2 . 0   -   5 0 )   { 
 
 	 	 	 	 	 s e t S u b T a s k ( T a s k F a c t o r y V 2 : : I n s t a n c e ( ) - > S m a r t G o t o P o s i t i o n ( c h a s e _ k i c k _ t a s k ) ) ; 
 
 	 	 	 	 } 
 
 	 	 	 }   e l s e   { 
 
 	 	 	 	 s e t S u b T a s k ( T a s k F a c t o r y V 2 : : I n s t a n c e ( ) - > S m a r t G o t o P o s i t i o n ( c h a s e _ k i c k _ t a s k ) ) ; 
 
 	 	 	 } 
 
 	 	 } 
 
 	 } 
 
 	 e l s e 
 
 	 { 
 
 	 	 / / c o u t   < <   " F U C K   B A L L   0 "   < < e n d l ; 
 
 	 	 d o u b l e   e n d _ v e l   =   0 ; 
 
                 d o u b l e   E N D V E L _ E N D X   =   P a r a m : : F i e l d : : P I T C H _ L E N G T H   /   2   -   P a r a m : : F i e l d : : P E N A L T Y _ A R E A _ D E P T H   -   C H A S E K I C K _ T O P E N A L T Y _ G A P ; 
 
 	 	 i f   ( m e . X ( )   >   C H A S E K I C K _ E N D V E L _ S T A R T X   & &   m e . X ( )   <   E N D V E L _ E N D X   & &   E N D V E L _ E N D X   >   C H A S E K I C K _ E N D V E L _ S T A R T X )   { 
 
 	 	 	 e n d _ v e l   =   ( C H A S E K I C K _ M A X E N D V E L   -   0 )   /   ( E N D V E L _ E N D X   -   C H A S E K I C K _ E N D V E L _ S T A R T X )   *     ( m e . X ( )   -   E N D V E L _ E N D X ) ; 
 
 	 	 	 / / G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ l i n e ( C G e o P o i n t ( m e . X ( ) ,   e n d _ v e l ) ,   C G e o P o i n t ( E N D V E L _ E N D X ,   0 ) ) ; 
 
 	 	 } 
 
 	 	 i f   ( D E B U G _ E N G I N E )   G D e b u g E n g i n e : : I n s t a n c e ( ) - > g u i _ d e b u g _ m s g ( b a l l . P o s ( ) ,   " g e t b a l l " ,   C O L O R _ P U R P L E ) ; 
 
 	 	 s e t S u b T a s k ( P l a y e r R o l e : : m a k e I t N o n e T r a j G e t B a l l ( t a s k ( ) . e x e c u t o r , f i n a l K i c k D i r ,   C V e c t o r ( 2   *   e n d _ v e l   *   c o s ( f i n a l K i c k D i r ) ,   2   *   e n d _ v e l   *   s i n ( f i n a l K i c k D i r ) ) , t a s k ( ) . p l a y e r . f l a g , - 2 ) ) ; 
 
 	 } 
 
 	 C S t a t e d T a s k : : p l a n ( p V i s i o n ) ; 
 
 } 
 
 
 
 C P l a y e r C o m m a n d *   C C h a s e K i c k V 1 : : e x e c u t e ( c o n s t   C V i s i o n M o d u l e *   p V i s i o n ) 
 
 { 
 
 	 i f (   s u b T a s k ( )   ) { 
 
 	 	 r e t u r n   s u b T a s k ( ) - > e x e c u t e ( p V i s i o n ) ; 
 
 	 } 
 
 	 i f (   _ d i r e c t C o m m a n d   ! =   N U L L   ) { 
 
 	 	 r e t u r n   _ d i r e c t C o m m a n d ; 
 
 	 } 
 
 	 r e t u r n   N U L L ; 
 
 } 
 
 