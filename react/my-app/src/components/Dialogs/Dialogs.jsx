import React from "react";
import s from "./Dialogs.module.css";

const Dialogs = (props) => {
  return (
    <div className={s.dialogs}>
      <div className={s.dialogsItems}>
        <div className={s.dialog}>Dimych</div>
        <div className={s.dialog}>Andrey</div>
        <div className={s.dialog + " " + s.active}>Sveta</div>
        <div className={s.dialog}>Sasha</div>
        <div className={s.dialog}>Valera</div>
        <div className={s.dialog}>Petr</div>
      </div>
      <div className={s.messages}>
        <div className={s.message}>Hi</div>
        <div className={s.message}>LOL</div>
        <div className={s.message}>Hello</div>
      </div>
    </div>
  );
};

export default Dialogs;
