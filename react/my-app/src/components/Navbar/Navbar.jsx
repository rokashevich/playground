import React from "react";
import s from "./Navbar.module.css";
console.log(s);

const Navbar = () => {
  return (
    <nav className={s.nav}>
      <div className={s.item}>
        <a href='/profile'>Profile</a>
      </div>
      <div className={s.item}>
        <a href='/dialogs'>Dialogs</a>
      </div>
      <div className={`${s.item} ${s.active}`}>
        <a>Messages</a>
      </div>
      <div className={s.item}>
        <a href='/news'>News</a>
      </div>
      <div className={s.item}>
        <a href='/music'>Music</a>
      </div>
      <div className={s.item}>
        <a href='/settings'>Settings</a>
      </div>

      <div className={s.b}>
        <a>b1</a>
      </div>
      <div className={`${s.b} ${s.active}`}>
        <a>b2</a>
      </div>
    </nav>
  );
};

export default Navbar;
