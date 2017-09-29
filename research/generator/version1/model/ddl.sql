create table user ( 
  user_id      varchar(16), 
  tags      varchar(21), 
  primary key (user_id), 
); 

create table role ( 
  role_id      varchar(5), 
  primary key (role_id), 
); 

create table sect ( 
  sect_id      varchar(6), 
  tags      varchar(6), 
  primary key (sect_id), 
); 

create table actor ( 
  actor_id      varchar(9), 
  tags      varchar(13), 
  primary key (actor_id), 
); 

create table video ( 
  video_id      varchar(17), 
  tags      varchar(46), 
  primary key (video_id), 
); 

create table follow ( 
  src_id      varchar(16), 
  tgt_id      varchar(16), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references user (user_id), 
); 

create table browse_video ( 
  src_id      varchar(16), 
  tgt_id      varchar(17), 
  primary key (src_id, tgt_id), 
  foreign key (src_id) references user (user_id), 
  foreign key (tgt_id) references video (video_id), 
); 


