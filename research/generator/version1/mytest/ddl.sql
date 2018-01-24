create table user ( 
  user_id      varchar(16) primary key, 
  tags      varchar(21) 
); 

create table role ( 
  role_id      varchar(5) primary key 
); 

create table sect ( 
  sect_id      varchar(6) primary key, 
  tags      varchar(6) 
); 

create table actor ( 
  actor_id      varchar(9) primary key, 
  tags      varchar(13) 
); 

create table video ( 
  video_id      varchar(17) primary key, 
  tags      varchar(46) 
); 

create table follow ( 
  src_id      varchar(16), 
  tgt_id      varchar(16), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references user (user_id) 
); 

create table browse_video ( 
  src_id      varchar(16), 
  tgt_id      varchar(17), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references video (video_id) 
); 

