type state = {
  name: string,
  email: string,
};

type action =
  | Change(string, string)
  | Submit;

let component = ReasonReact.statelessComponent("Register");

let doStuff = event => {
  ReactEvent.Form.preventDefault(event);
  Js.log("Do stuff");
};

// Todo add actions for onChange and onSubmit

let make = _children => {
  ...component,

  render: _self =>
    <div>
      <form onSubmit=doStuff>
        // <input type_="text" placeholder="Name" onChange = {
        //   event => send(Change(ReactEvent.Form.target(event)##value));
        // } />

          <input type_="text" name="name" placeholder="Name" />
          <input type_="email" name="email" placeholder="Email" />
          <button type_="submit"> {ReasonReact.string("Submit")} </button>
        </form>
    </div>,
};